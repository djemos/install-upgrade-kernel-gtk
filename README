# install-upgrade-kernel-gtk
install-upgrade-kernel is a script that make easy to install kernel packages 
without removing the previous kernel packages and 
upgrading grub menus boot loader.
install-upgrade-kernel-gtk is a front-end, the gui tool of the script 
which is written in c using glade and gtk3.
It is used for installations of slackel or salix on internal disks.

install-upgarade-kernel-gtk can be used on any slackware or slackware based
system. 

To download and create the package type:
mkdir build
cd build
git clone https://github.com/djemos/install-upgrade-kernel-gtk.git

mv install-upgrade-kernel-gtk/SLKBUILD ./

tar -cvjSf install-upgrade-kernel-gtk.tar.bz2 install-upgrade-kernel-gtk

fakeroot slkbuild -X

To install the package type: 
for 64bit:
sudo spkg install-upgrade-kernel-gtk-1.0-x86_64-1dj.txz   

or for 32bit:
sudo spkg install-upgrade-kernel-gtk-1.0-i586-1dj.txz  


Copyright (C) 2022 Dimitris Tzemos <dijemos@gmail.com>
This program is free software: you can redistribute it and/or modify it under the terms 
of the GNU General Public License as published by the Free Software Foundation, 
either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty 
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License at <http://www.gnu.org/licenses/> for more details.
