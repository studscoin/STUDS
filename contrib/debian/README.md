
Debian
====================
This directory contains files used to package studscoind/studscoin-qt
for Debian-based Linux systems. If you compile studscoind/studscoin-qt yourself, there are some useful files here.

## studscoin: URI support ##


studscoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install studscoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your studscoinqt binary to `/usr/bin`
and the `../../share/pixmaps/studscoin128.png` to `/usr/share/pixmaps`

studscoin-qt.protocol (KDE)

