#!/bin/zsh
cd -- "${0:A:h}"
export TK_SILENCE_DEPRECATION=1
exec python3 tools/notecomplete_launcher.py
