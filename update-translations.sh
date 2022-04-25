#!/bin/sh

intltool-extract --type="gettext/ini" src/install-upgrade-kernel-gtk.desktop.in
intltool-extract --type="gettext/ini" src/install-upgrade-kernel-gtk-kde.desktop.in

xgettext --from-code=utf-8 \
	-L Glade \
	-o po/install-upgrade-kernel-gtk.pot \
	src/install-upgrade-kernel-gtk.ui

xgettext --from-code=utf-8 \
	-j \
	-L Python \
	-o po/install-upgrade-kernel-gtk.pot \
	src/install-upgrade-kernel-gtk.c
xgettext --from-code=utf-8 -j -L C -kN_ -o po/install-upgrade-kernel-gtk.pot src/install-upgrade-kernel-gtk.desktop.in.h
xgettext --from-code=utf-8 -j -L C -kN_ -o po/install-upgrade-kernel-gtk.pot src/install-upgrade-kernel-gtk-kde.desktop.in.h

rm src/install-upgrade-kernel-gtk.desktop.in.h src/install-upgrade-kernel-gtk-kde.desktop.in.h

cd po
for i in `ls *.po`; do
	msgmerge -U $i install-upgrade-kernel-gtk.pot
done
rm -f ./*~
