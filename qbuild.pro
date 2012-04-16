# Copyright (c) 2012 Radek Polak

TEMPLATE=app

# The binary name
TARGET=qtmoko-freecell

# This app uses Qtopia
CONFIG+=qtopia

DEFINES+=QTOPIA

QT += svg

SOURCES += main.cpp \
    freecell.cpp \
    freecellview.cpp \
    cselectgamedlg.cpp \
    cstatistics.cpp \
    cstatisticsdata.cpp \
    cselectgamedlgdata.cpp \
    coptions.cpp \
    cards.cpp \
    freecelldoc.cpp \
    coptionsdata.cpp

HEADERS += resource.h \
    main.h \
    freecellview.h \
    freecelldoc.h \
    freecell.h \
    cstatistics.h \
    cselectgamedlg.h \
    coptions.h \
    cards.h
    
RESOURCES = qresources.qrc

pkg [
    name=qtmoko-freecell
    desc="freecell"
    version=$$QTOPIA_VERSION
    license=$$QTOPIA_LICENSE
    maintainer=$$QTOPIA_MAINTAINER
]

target [
    hint=sxe
    domain=trusted
]

desktop [
    hint=desktop
    files=qtmoko-freecell.desktop
    path=/apps/Games
]

pics [
    hint=pics
    files=qtmoko-freecell.svg
    path=/pics/qtmoko-freecell
]
