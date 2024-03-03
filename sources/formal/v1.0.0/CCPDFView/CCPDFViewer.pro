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
    source/core/pdf_exportpdfex.cpp \
    source/window/UI/reminderprocesswindow.cpp \
    source/core/pdf_editedpagemanager.cpp \
    source/core/PDF_EditGraphicView.cpp \
    source/core/PDF_Utils.cpp \
    source/core/ThemeHandler.cpp \
    source/core/ccpdf_loader.cpp \
    source/core/ccpdf_view.cpp \
    source/core/eventhandler.cpp \
    source/core/main.cpp \
    source/core/notehandle.cpp \
    source/core/paintingpackage.cpp \
    source/core/pdf_edithistoricalrecorder.cpp \
    source/core/pdf_fileviewmanager.cpp \
    source/core/pdf_historicalrecord.cpp \
    source/core/pdfloaderrorhandle.cpp \
    source/window/UI/editpdf_mainwindow.cpp \
    source/window/UI/helpmainwindow.cpp \
    source/window/UI/mainwindow.cpp \
    source/window/UI/ocr_mainwindow.cpp \
    source/window/UI/qssmanager.cpp \
    source/window/windowCore/markerpropertysetter.cpp


HEADERS += \
    include/core/PDF_MessageBox.h \
    include/core/PDF_PathSettings.h \
    include/core/PDF_Utils.h \
    include/core/ThemeHandler.h \
    include/core/ccpdf_loader.h \
    include/core/ccpdf_view.h \
    include/core/eventhandler.h \
    include/core/notehandle.h \
    include/core/ocrpackage.h \
    include/core/paintingpackage.h \
    include/core/pdf_editgraphicview.h \
    include/core/pdf_edithistoricalrecorder.h \
    include/core/pdf_fileviewmanager.h \
    include/core/pdf_historicalrecord.h \
    include/core/pdfloaderrorhandle.h \
    include/window/UI/editpdf_mainwindow.h \
    include/window/UI/helpmainwindow.h \
    include/window/UI/mainwindow.h \
    include/window/UI/ocr_mainwindow.h \
    include/window/UI/qssmanager.h \
    include/window/windowCore/PDF_Edit_Utils.h \
    include/window/windowCore/markerpropertysetter.h \
    include/window/windowCore/pdf_Reactor.h \
    include/core/pdf_editedpagemanager.h \
    include/core/pdf_exportpdfex.h \
    include/window/UI/reminderprocesswindow.h

FORMS += \
    editpdf_mainwindow.ui \
    helpmainwindow.ui \
    mainwindow.ui \
    ocr_mainwindow.ui \
    reminderprocesswindow.ui

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

else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ocr/libs/debug/mingw/ -lOCRPack


debug{
    DEFINES += CCPDF_VIEW_DEBUG
}

INCLUDEPATH += $$PWD/ocr/libs/debug/mingw
DEPENDPATH += $$PWD/ocr/libs/debug/mingw

