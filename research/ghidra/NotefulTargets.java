//@category Noteful.RE
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Reference;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.util.*;
import com.google.gson.*;

/** Read-only target discovery from diagnostic strings and nearby metadata references. */
public class NotefulTargets extends GhidraScript {
    public void run() throws Exception {
        Path out = Paths.get(getScriptArgs()[0]);
        Files.createDirectories(out);
        JsonArray records = new JsonArray();
        Set<Function> functions = new LinkedHashSet<>();
        for (String seed : new String[]{"100991034", "100adf5f4", "100ae2254", "100ae186c", "100ae197c"}) {
            Function f = getFunctionContaining(toAddr(seed));
            if (f != null) functions.add(f);
        }
        String[] needles = {"StrokeDecoder.parse", "StrokeDecoder", "StrokeEncoder", "PackageFileReader",
            "PackageFileWriter", "FastBinaryDecoder", "SwiftBinaryDecoder", "BinaryEncoder",
            "Decode failed at strokes:", "Corrupted stroke set file"};
        for (String needle : needles) {
            byte[] pattern = needle.getBytes(StandardCharsets.UTF_8);
            Address cursor = currentProgram.getMinAddress();
            int count = 0;
            while (cursor != null && count++ < 100) {
                Address hit = currentProgram.getMemory().findBytes(cursor, pattern, null, true, monitor);
                if (hit == null) break;
                JsonObject record = new JsonObject();
                record.addProperty("needle", needle); record.addProperty("address", hit.toString());
                JsonArray refs = new JsonArray();
                for (Reference ref : getReferencesTo(hit)) {
                    JsonObject rr = new JsonObject();
                    rr.addProperty("from", ref.getFromAddress().toString());
                    Function f = getFunctionContaining(ref.getFromAddress());
                    if (f != null) {
                        rr.addProperty("function", f.getEntryPoint().toString());
                        rr.addProperty("name", f.getName()); functions.add(f);
                    }
                    // A C string can be referenced through a CFConstantString (+16).
                    JsonArray indirect = new JsonArray();
                    for (int delta : new int[]{0, -16}) {
                        for (Reference second : getReferencesTo(ref.getFromAddress().add(delta))) {
                            Function ff = getFunctionContaining(second.getFromAddress());
                            if (ff != null) {
                                JsonObject ir = new JsonObject();
                                ir.addProperty("from", second.getFromAddress().toString());
                                ir.addProperty("via", ref.getFromAddress().add(delta).toString());
                                ir.addProperty("function", ff.getEntryPoint().toString());
                                indirect.add(ir); functions.add(ff);
                            }
                        }
                    }
                    rr.add("indirect_code_references", indirect);
                    refs.add(rr);
                }
                record.add("references", refs); records.add(record);
                cursor = hit.add(1);
            }
        }
        Files.writeString(out.resolve("string-targets.json"), new GsonBuilder().setPrettyPrinting().create().toJson(records));
        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        int count = 0;
        for (Function f : functions) {
            if (count++ >= 20) break;
            DecompileResults r = decompiler.decompileFunction(f, 15, monitor);
            String text = "// " + f.getEntryPoint() + " " + f.getName() + "\n";
            text += r.decompileCompleted() ? r.getDecompiledFunction().getC() : r.getErrorMessage();
            Files.writeString(out.resolve(f.getEntryPoint() + ".c"), text);
        }
        decompiler.dispose();
        println("Noteful targets: " + records.size() + " string matches; " + functions.size() + " functions");
    }
}
