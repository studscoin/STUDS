
Debian
====================
This directory contains files used to package studsd/studs-qt
for Debian-based Linux systems. If you compile studsd/studs-qt yourself, there are some useful files here.

## pivx: URI support ##


studs-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install studs-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your studs-qt binary to `/usr/bin`
and the `../../share/pixmaps/pivx128.png` to `/usr/share/pixmaps`

studs-qt.protocol (KDE)

