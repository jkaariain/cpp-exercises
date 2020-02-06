TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    splitter.cpp \
    tiedostonlukija.cpp \
    kayttoliittyma.cpp

HEADERS += \
    splitter.hh \
    tiedostonlukija.hh \
    kayttoliittyma.hh \
    tuote.hh
