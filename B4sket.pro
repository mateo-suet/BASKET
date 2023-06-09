QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BDD.cpp \
    equipe.cpp \
    main.cpp \
    mdp.cpp \
    new_mdp.cpp \
    parametre.cpp \
    puissance4.cpp \
    resultat.cpp

HEADERS += \
    BDD.h \
    equipe.h \
    mdp.h \
    new_mdp.h \
    parametre.h \
    puissance4.h \
    resultat.h

FORMS += \
    equipe.ui \
    mdp.ui \
    new_mdp.ui \
    parametre.ui \
    puissance4.ui \
    resultat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
