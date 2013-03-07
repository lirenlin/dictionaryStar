#############################################################################
# src.pro - DictionaryStar, stardict dictionary for MeeGo Harmattan         #
# Copyright (C) 2012 Jari P.T. Alhonen                                      #
#                                                                           #
# This program is free software; you can redistribute it and/or modify      #
# it under the terms of the GNU General Public License as published by      #
# the Free Software Foundation; either version 3 of the License, or         #
# (at your option) any later version.                                       #
#                                                                           #
# This program is distributed in the hope that it will be useful,           #
# but WITHOUT ANY WARRANTY; without even the implied warranty of            #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             #
# GNU General Public License for more details.                              #
#                                                                           #
# You should have received a copy of the GNU General Public License along   #
# with this program; if not, see <http://www.gnu.org/licenses/>.            #
#############################################################################

include(../DictionaryStar.pri)

TEMPLATE = app
TARGET = myApp
target.path = $${INSTALL_PREFIX}/bin

OBJECTS_DIR = .obj
MOC_DIR = .moc
M_MGEN_OUTDIR = .gen

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qdeclarative-boostable

#CONFIG += opengl
QT += sql

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    dictcore.cpp \
    dictwebview.cpp \
    tableModel.cpp \
    sqlmodel.cpp \
    database.cpp

HEADERS += \
    dictcore.h \
    tableModel.h \
    ../plugins/dictplugin.h \
    dictwebview.h \
    qwebviewselectionsuppressor.h \
    sqlmodel.h \
    database.h

RESOURCES += \
    ../resources.qrc

INSTALLS += target
