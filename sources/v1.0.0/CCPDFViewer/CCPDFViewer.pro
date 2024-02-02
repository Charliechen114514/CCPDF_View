QT       += core gui
# Make PDF load enable(Link Libraries)
QT       += pdf
QT       += pdfwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    source/window/UI/helpmainwindow.cpp \
    source/core/ThemeHandler.cpp \
    source/core/notehandle.cpp \
    source/window/UI/ocr_mainwindow.cpp \
    source/core/pdf_fileviewmanager.cpp \
    source/core/PDF_Utils.cpp \
    source/core/ccpdf_loader.cpp \
    source/core/ccpdf_view.cpp \
    source/core/eventhandler.cpp \
    source/core/main.cpp \
    source/core/pdf_historicalrecord.cpp \
    source/core/pdfloaderrorhandle.cpp \
    source/window/UI/mainwindow.cpp \
    source/window/UI/editpdf_mainwindow.cpp \
    source/window/UI/qssmanager.cpp


HEADERS += \
    include/window/UI/helpmainwindow.h \
    include/core/PDF_PathSettings.h \
    include/core/ThemeHandler.h \
    include/core/ocrpackage.h \
    include/window/UI/editpdf_mainwindow.h \
    include/core/PDF_MessageBox.h \
    include/core/PDF_Utils.h \
    include/core/PDF_Utils.h \
    include/core/ccpdf_loader.h \
    include/core/ccpdf_view.h \
    include/core/eventhandler.h \
    include/core/pdf_historicalrecord.h \
    include/core/pdfloaderrorhandle.h \
    include/window/UI/mainwindow.h \
    include/core/pdf_historicalrecord.h \
    include/core/PDF_MessageBox.h \
    include/window/windowCore/pdf_Reactor.h \
    include/core/pdf_fileviewmanager.h \
    include/window/UI/ocr_mainwindow.h \
    include/core/notehandle.h \
    include/window/UI/qssmanager.h

FORMS += \
    editpdf_mainwindow.ui \
    helpmainwindow.ui \
    mainwindow.ui \
    ocr_mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin


INCLUDEPATH += "D:/QT projects/CCPDFViewer/include/core" \
            += "D:/QT projects/CCPDFViewer/include/window" \
            += "D:/QT projects/CCPDFViewer/include/window/UI" \
            += "D:/QT projects/CCPDFViewer/include/window/windowCore"

!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Direct/dark/darkstyle.qrc \
    Direct/light/lightstyle.qrc \
    QSS_I.qrc \
    icons.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ocr/libs/release/mingw/ -lOCRPack \

else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ocr/libs/release/mimgw/ -lOCRPack


debug{
    # DEFINES += CCPDF_VIEW_DEBUG
}

INCLUDEPATH += $$PWD/ocr/libs/debug/mingw
DEPENDPATH += $$PWD/ocr/libs/debug/mingw

