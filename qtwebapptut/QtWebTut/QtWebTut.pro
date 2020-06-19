QT += network
CONFIG += c++11 console
CONFIG -= app_bundle
QT += sql

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        categoriescontroller.cpp \
        categoryadd.cpp \
        changeitemcontroller.cpp \
        cookietestcontroller.cpp \
        global.cpp \
        itemaddingcontroller.cpp \
        logincontroller.cpp \
        logout.cpp \
        main.cpp \
        mainpagecontroller.cpp \
        otherusersitemscontroller.cpp \
        registercontroller.cpp \
        requestmapper.cpp \
        sqlconnection.cpp \
        useritemscontroller.cpp \
        userlistcontroller.cpp

OTHER_FILES += etc/webapp1.ini


include(../QtWebApp/QtWebApp/httpserver/httpserver.pri)
include(../QtWebApp/QtWebApp/templateengine/templateengine.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    categoriescontroller.h \
    categoryadd.h \
    changeitemcontroller.h \
    cookietestcontroller.h \
    global.h \
    itemaddingcontroller.h \
    logincontroller.h \
    logout.h \
    mainpagecontroller.h \
    otherusersitemscontroller.h \
    registercontroller.h \
    requestmapper.h \
    sqlconnection.h \
    useritemscontroller.h \
    userlistcontroller.h

DISTFILES += \
    docroot/files/style.css

win32: LIBS += -L$$PWD/'../../../../../Program Files/MySQL/MySQL Server 8.0/lib/' -llibmysql

INCLUDEPATH += $$PWD/'../../../../../Program Files/MySQL/MySQL Server 8.0/include'
DEPENDPATH += $$PWD/'../../../../../Program Files/MySQL/MySQL Server 8.0/include'
