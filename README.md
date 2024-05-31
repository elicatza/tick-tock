# Tick-Tock
My pomodoro timer using system notifications.
Only tested on Linux, but should work on other all systems with notify-send.

## Dependencies
- [adwaita-icon-theme](https://gitlab.gnome.org/GNOME/adwaita-icon-theme)
- [libnotify](https://gitlab.gnome.org/GNOME/libnotify)
- [libprocps](https://gitlab.com/procps-ng/procps/)

## Install
```bash
git clone "https://github.com/elicatza/tick-tock" --depth 1
cd tick-tock
make
sudo make install

# For local install run:
# make install PREFIX=~/.local
```

## Uninstall
```bash
# Navigate into clone directory
make uninstall

# For local uninstall run:
# make uninstall PREFIX=~/.local
```

## TODO
Command line arguments for time and notify-send flags.
There should also be a flag to reset timer.
