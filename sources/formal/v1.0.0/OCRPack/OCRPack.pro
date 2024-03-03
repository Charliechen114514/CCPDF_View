QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# TO EXPORT LIBS, decomment followings
DEFINES += OCRPACKAGE_LIBRARY
TEMPLATE = lib

# disable main.cpp to prevent the main symbol
SOURCES += \
        # main.cpp \
        ocr_detectinfo.cpp \
        ocrerrorstringadapter.cpp \
        ocrpackage.cpp \
        ocrpackagecore.cpp \
        ocrpackageprivate.cpp \
        ocrsingtonspackages.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ocr_detectinfo.h \
    ocrerrorstringadapter.h \
    ocrpackage.h \
    ocrpackagecore.h \
    ocrpackageprivate.h \
    ocrsingtonspackages.h
