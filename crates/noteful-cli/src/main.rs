use noteful_core::{Package, MAX_FILE_BYTES};
use std::{
    io::{self, Read, Write},
    process::ExitCode,
};

fn run() -> Result<(), Box<dyn std::error::Error>> {
    let mut args = std::env::args_os().skip(1);
    let cmd = args
        .next()
        .ok_or("Usage: noteful inspect|verify|render <file|->")?;
    let source = args.next().ok_or("Missing input file (or - for stdin)")?;
    if args.next().is_some() {
        return Err("Too many arguments".into());
    }
    if cmd != "inspect" && cmd != "verify" && cmd != "render" {
        return Err("Expected inspect, verify or render".into());
    }
    let input: Box<dyn Read> = if source == "-" {
        Box::new(io::stdin())
    } else {
        Box::new(std::fs::File::open(source)?)
    };
    let mut data = Vec::new();
    input
        .take((MAX_FILE_BYTES + 1) as u64)
        .read_to_end(&mut data)?;
    if cmd == "render" {
        let editor = noteful_core::Editor::open(&data)?;
        let pages = (0..editor.scene.pages.len())
            .map(|i| editor.view(i))
            .collect::<Result<Vec<_>, _>>()?;
        serde_json::to_writer(
            io::stdout().lock(),
            &serde_json::json!({"title":editor.scene.title,"pages":pages}),
        )?;
        return Ok(());
    }
    let package = Package::parse(&data)?;
    if cmd == "verify" {
        if package.rebuild()? != data {
            return Err("Round-trip mismatch".into());
        }
        println!(
            "Verified {} bytes, {} blocks; byte-exact round-trip",
            data.len(),
            package.blocks.len()
        );
    } else {
        let mut stdout = io::BufWriter::new(io::stdout().lock());
        serde_json::to_writer(&mut stdout, &package.to_json())?;
        stdout.write_all(b"\n")?;
    }
    Ok(())
}
fn main() -> ExitCode {
    match run() {
        Ok(()) => ExitCode::SUCCESS,
        Err(e) => {
            eprintln!("Error: {e}");
            ExitCode::FAILURE
        }
    }
}
