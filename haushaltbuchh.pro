QT       += core gui
QT += core gui charts
QT += core gui network
CONFIG += static
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ausgabe.cpp \
    buchung.cpp \
    buchungbearbeiten.cpp \
    buchungenanschauen.cpp \
    einnahme.cpp \
    main.cpp \
    mainwindow.cpp \
    neuebuchung.cpp \
    neuerbarchart.cpp \
    neuerpiechart.cpp \
    neuersparplan.cpp \
    profil.cpp \
    rechnung.cpp \
    sparplaeneanschauen.cpp \
    sparplan.cpp \
    sparplanbearbeiten.cpp

HEADERS += \
    ausgabe.h \
    buchung.h \
    buchungbearbeiten.h \
    buchungenanschauen.h \
    einnahme.h \
    mainwindow.h \
    neuebuchung.h \
    neuerbarchart.h \
    neuerpiechart.h \
    neuersparplan.h \
    profil.h \
    rechnung.h \
    sparplaeneanschauen.h \
    sparplan.h \
    sparplanbearbeiten.h

FORMS += \
    buchungbearbeiten.ui \
    buchungenanschauen.ui \
    mainwindow.ui \
    neuebuchung.ui \
    neuersparplan.ui \
    profil.ui \
    sparplaeneanschauen.ui \
    sparplanbearbeiten.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
