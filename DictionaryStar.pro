################################################################################
# DictionaryStar.pro - DictionaryStar, stardict dictionary for MeeGo Harmattan #
# Copyright (C) 2012 Jari P.T. Alhonen                                         #
#                                                                              #
# This program is free software; you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation; either version 3 of the License, or            #
# (at your option) any later version.                                          #
#                                                                              #
# This program is distributed in the hope that it will be useful,              #
# but WITHOUT ANY WARRANTY; without even the implied warranty of               #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                #
# GNU General Public License for more details.                                 #
#                                                                              #
# You should have received a copy of the GNU General Public License along      #
# with this program; if not, see <http://www.gnu.org/licenses/>.               #
################################################################################

include(DictionaryStar.pri)
TEMPLATE = subdirs
SUBDIRS = src plugins

unix: isEmpty(INSTALL_PREFIX):INSTALL_PREFIX=/usr

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += glib-2.0
    LIBS += -lz -larchive
}
macx {
    # universal binaries
    CONFIG += x86 #x86_64 # not available on Snow Leopard ppc ppc64
#    QMAKE_MAC_SDK = /Developer/SDKs/MacOSX10.5.sdk/
}
win32 {
    CONFIG += console
# TODO: check what is the libarchive dll really called under win32!
    LIBS += -lzdll -lglib-2.0 -luser32 -larchive
    INCLUDEPATH += $$GLIB2PATH/include/glib-2.0 \
                   $$GLIB2PATH/lib/glib-2.0/include \
                   $$ZLIBPATH/include
    QMAKE_LIBDIR += $$GLIB2PATH/lib \
                    $$ZLIBPATH/lib
}

qml_data.path = $${INSTALL_PREFIX}/qml
qml_data.files = qml/*.qml

desktops_data.path = /usr/share/applications
desktops_data.files = DictionaryStar.desktop

images_data.path = /usr/share/themes/base/meegotouch/icons
images_data.files = images/DictionaryStar.svg

INSTALLS += desktops_data \
            images_data \
            qml_data

