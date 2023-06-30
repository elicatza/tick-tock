# Tick-Tock
My pomodoro timer using system notifications.
Only tested on Linux, but should work on other all systems with notify-send.

## Requirements
Running
- [libnotify](https://gitlab.gnome.org/GNOME/libnotify)
- flock
- pgrep

## Install
```bash
git clone "https://github.com/elicatza/tick-tock" --depth 1
cd tick-tock
make install

# For local install run:
# make install DESTDIR=~/.local/bin
```

## Uninstall
```bash
# Navigate to clone directory
make uninstall
# For local uninstall run:
# make uninstall DESTDIR=~/.local/bin
```

## TODO
Command line arguments for time and notify-send flags.
There should also be a flag to reset timer.
