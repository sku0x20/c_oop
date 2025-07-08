#!/usr/bin/env python3

import sys
from pathlib import Path
from watchdog.events import FileSystemEvent, FileSystemEventHandler
from watchdog.observers import Observer

if len(sys.argv) < 2:
    print("Usage: watch.py <dir1> [<dir2> ...]")
    sys.exit(1)
dirs = sys.argv[1:]

buildFile = Path("meson.build")
def touchBuild(event):
    buildFile.touch()

class CustomEventHandler(FileSystemEventHandler):
    def on_created(self, event: FileSystemEvent) -> None:
        touchBuild(event)
    def on_deleted(self, event: FileSystemEvent) -> None:
        touchBuild(event)
    def on_moved(self, event: FileSystemEvent) -> None:
        touchBuild(event)

event_handler = CustomEventHandler()
observer = Observer()

for dir in dirs:
    observer.schedule(event_handler, dir, recursive=True)

observer.start()

try:
    print("watching filesystem changes...")
    while True:
        input()
except KeyboardInterrupt:
    pass
finally:
    observer.stop()
    observer.join()
