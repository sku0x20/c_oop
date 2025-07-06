#!/usr/bin/env python3

from os import walk
import sys

if len(sys.argv) < 2:
    print("Usage: grab_files.py <dir1> [<dir2> ...]")
    sys.exit(1)
srcDirs = sys.argv[1:]

files = []

for srcDir in srcDirs:
    for (dirpath, dirnames, filenames) in walk(f'{srcDir}'):
        for filename in filenames:
            if filename.endswith('.c'):
                files.append(f"{dirpath}/{filename}")

for cFile in files:
    print(cFile)
