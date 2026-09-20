#!/usr/bin/env python3
from pathlib import Path
import subprocess
import tkinter as tk
import webbrowser

ROOT = Path(__file__).resolve().parents[1]

VERSIONS = (
    (
        "NoteComplete",
        8771,
        ("python3", "-m", "http.server", "8771", "--directory", "work/ui-review"),
        "http://127.0.0.1:8771/notecomplete-direction-preview.html",
    ),
    ("Legacy viewer", 8767, ("node", "tools/serve_web.mjs", "8767"), "http://127.0.0.1:8767/"),
)


class Launcher:
    def __init__(self, root):
        self.root = root
        self.processes = {}
        background = "#eef3f8"
        root.configure(background=background)
        root.geometry("300x250")
        root.title("NoteComplete")
        root.resizable(False, False)
        root.protocol("WM_DELETE_WINDOW", self.close)

        frame = tk.Frame(root, background=background, padx=18, pady=18)
        frame.grid()
        tk.Label(frame, text="NoteComplete", background=background, foreground="#1f2d3d", font=("TkDefaultFont", 16, "bold")).grid(
            row=0, column=0, sticky="w"
        )
        tk.Label(frame, text="Abrir una version", background=background, foreground="#596b82").grid(row=1, column=0, sticky="w", pady=(2, 14))

        for row, (name, _, _, _) in enumerate(VERSIONS, start=2):
            tk.Button(frame, text=name, command=lambda version=name: self.launch(version), background="#ffffff", foreground="#1f2d3d", activebackground="#dce9fb", activeforeground="#1f2d3d", relief="flat", borderwidth=0, padx=14, pady=8, anchor="w").grid(
                row=row, column=0, sticky="ew", pady=3
            )

        self.status = tk.Label(frame, text="Listo", background=background, foreground="#596b82", anchor="w")
        self.status.grid(row=5, column=0, sticky="w", pady=(14, 0))
        root.update_idletasks()

        window_width = root.winfo_reqwidth()
        window_height = root.winfo_reqheight()
        x = max(0, (root.winfo_screenwidth() - window_width) // 2)
        y = max(0, (root.winfo_screenheight() - window_height) // 2)
        root.geometry(f"{window_width}x{window_height}+{x}+{y}")

        root.deiconify()
        root.lift()

    def launch(self, name):
        version = next(version for version in VERSIONS if version[0] == name)
        _, port, command, url = version
        process = self.processes.get(port)
        if process is None or process.poll() is not None:
            log_path = Path("/tmp") / f"notecomplete-launcher-{port}.log"
            log = log_path.open("ab")
            process = subprocess.Popen(command, cwd=ROOT, stdout=log, stderr=subprocess.STDOUT)
            self.processes[port] = (process, log)
        self.status.configure(text=f"Abriendo {name}...")
        self.root.after(400, lambda: self.open_url(name, url))

    def open_url(self, name, url):
        webbrowser.open(url)
        self.status.configure(text=f"Abierto: {name}")

    def close(self):
        for process, log in self.processes.values():
            if process.poll() is None:
                process.terminate()
            log.close()
        self.root.destroy()


if __name__ == "__main__":
    window = tk.Tk()
    Launcher(window)
    window.mainloop()
