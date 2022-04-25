#!/bin/sh

intltool-extract --type="gettext/ini" src/install-upgrade-kernel-ext-usb-gtk.desktop.in
intltool-extract --type="gettext/ini" src/install-upgrade-kernel-ext-usb-gtk-kde.desktop.in

xgettext --from-code=utf-8 \
	-L Glade \
	-o po/install-upgrade-kernel-ext-usb-gtk.pot \
	src/install-upgrade-kernel-ext-usb-gtk.ui

xgettext --from-code=utf-8 \
	-j \
	-L Python \
	-o po/install-upgrade-kernel-ext-usb-gtk.pot \
	src/install-upgrade-kernel-ext-usb-gtk.c
xgettext --from-code=utf-8 -j -L C -kN_ -o po/install-upgrade-kernel-ext-usb-gtk.pot src/install-upgrade-kernel-ext-usb-gtk.desktop.in.h
xgettext --from-code=utf-8 -j -L C -kN_ -o po/install-upgrade-kernel-ext-usb-gtk.pot src/install-upgrade-kernel-ext-usb-gtk-kde.desktop.in.h

rm src/install-upgrade-kernel-ext-usb-gtk.desktop.in.h src/install-upgrade-kernel-ext-usb-gtk-kde.desktop.in.h

cd po
for i in `ls *.po`; do
	msgmerge -U $i install-upgrade-kernel-ext-usb-gtk.pot
done
rm -f ./*~
