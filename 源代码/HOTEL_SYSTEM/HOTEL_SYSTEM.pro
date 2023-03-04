QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
RC_ICONS=  hotelsystem.ico
TARGET = XINHUA_HOTEL
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
    ClientPage/clientpage1.cpp \
    ClientPage/clientpage2.cpp \
    ClientPage/clientpage3.cpp \
    ClientPage/clientpage4.cpp \
    ClientPage/clientpage5.cpp \
    ClientPage/clientwidget.cpp \
    MyClass/myitemdelegate.cpp \
    MyClass/mypropertyanimation.cpp \
    MyClass/myrotatepictures.cpp \
    MyClass/myslidervalid.cpp \
    MyClass/mysqlmodel.cpp \
    MyClass/mysqlquerymodel.cpp \
    MyClass/mythread.cpp \
    SuperPage/superadmin.cpp \
    SuperPage/superpage1.cpp \
    SuperPage/superpage1edit.cpp \
    SuperPage/superpage2.cpp \
    SuperPage/superpage2edit.cpp \
    SuperPage/superpage3.cpp \
    SuperPage/superpage3edit.cpp \
    SuperPage/superpage4.cpp \
    SuperPage/superpage5.cpp \
    SuperPage/superpage5detail.cpp \
    SuperPage/superpage6.cpp \
    main.cpp \
    mainwindow.cpp \
    registerpage.cpp \
    registeruser.cpp \
    resetpassword.cpp \
    servicepage1.cpp \
    servicewidget.cpp \


HEADERS += \
    ClientPage/clientpage1.h \
    ClientPage/clientpage2.h \
    ClientPage/clientpage3.h \
    ClientPage/clientpage4.h \
    ClientPage/clientpage5.h \
    ClientPage/clientwidget.h \
    MyClass/myitemdelegate.h \
    MyClass/mypropertyanimation.h \
    MyClass/myrotatepictures.h \
    MyClass/myslidervalid.h \
    MyClass/mysqlmodel.h \
    MyClass/mysqlquerymodel.h \
    MyClass/mythread.h \
    SuperPage/superadmin.h \
    SuperPage/superpage1.h \
    SuperPage/superpage1edit.h \
    SuperPage/superpage2.h \
    SuperPage/superpage2edit.h \
    SuperPage/superpage3.h \
    SuperPage/superpage3edit.h \
    SuperPage/superpage4.h \
    SuperPage/superpage5.h \
    SuperPage/superpage5detail.h \
    SuperPage/superpage6.h \
    clientpage1.h \
    clientpage2.h \
    clientpage3.h \
    clientpage4.h \
    clientpage5.h \
    clientwidget.h \
    mainwindow.h \
    myitemdelegate.h \
    mypropertyanimation.h \
    myrotatepictures.h \
    myslidervalid.h \
    mysqlquerymodel.h \
    mythread.h \
    registerpage.h \
    registeruser.h \
    resetpassword.h \
    servicepage1.h \
    servicewidget.h \
    superadmin.h \
    superpage1.h \
    superpage1edit.h \
    superpage2.h \
    superpage2edit.h \
    superpage3.h \
    superpage3edit.h \
    superpage4.h \
    superpage5.h \
    superpage5detail.h \
    superpage6.h

FORMS += \
    clientpage1.ui \
    clientpage2.ui \
    clientpage3.ui \
    clientpage4.ui \
    clientpage5.ui \
    clientwidget.ui \
    mainwindow.ui \
    mypropertyanimation.ui \
    myrotatepictures.ui \
    mysqlquerymodel.ui \
    registerpage.ui \
    registeruser.ui \
    resetpassword.ui \
    servicepage1.ui \
    servicewidget.ui \
    superadmin.ui \
    superpage1.ui \
    superpage1edit.ui \
    superpage2.ui \
    superpage2edit.ui \
    superpage3.ui \
    superpage3edit.ui \
    superpage4.ui \
    superpage5.ui \
    superpage5detail.ui \
    superpage6.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qicon.qrc
