TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    merkkijonojoukko.cpp \
    kayttoliittyma.cpp \
    reseptikokoelma.cpp

HEADERS += \
    merkkijonojoukko.hh \
    kayttoliittyma.hh \
    reseptikokoelma.hh
