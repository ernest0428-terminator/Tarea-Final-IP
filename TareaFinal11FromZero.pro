TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    Logic/logic.c \
    Interface/interface.c \
    Interface/menu.c \
    Interface/report.c

HEADERS += \
    Logic/dats.h \
    Logic/logic.h \
    Interface/interface.h \
    Interface/menu.h \
    Interface/report.h \
    Logic/colors.h

