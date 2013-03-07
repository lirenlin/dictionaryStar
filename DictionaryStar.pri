################################################################################
# DictionaryStar.pri - DictionaryStar, stardict dictionary for MeeGo Harmattan #
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

QT       +=  webkit network declarative

symbian:TARGET.UID3 = 0xE42D2891

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

contains(MEEGO_EDITION,harmattan):INSTALL_PREFIX=/opt/myApp
unix: isEmpty(INSTALL_PREFIX):INSTALL_PREFIX=/usr/local

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += glib-2.0
    LIBS += -lz
    LIBS += -larchive
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

isEmpty(PLUGINS_DIR):PLUGINS_DIR=$${INSTALL_PREFIX}/lib/myApp/plugins
DEFINES += DICTSTAR_PLUGINS_DIR=\\\"$$INSTALL_PREFIX/lib/myApp/plugins\\\"
