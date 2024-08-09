QT       += core gui pdf pdfwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = resources/icons/mainWindow.ico

INCLUDEPATH += \
    Core \
    Debugging \
    Ui \
    Ui/CCPDF_MdiArea \
    Ui/CCPDF_BookLibraryWidget \
    Ui/CCPDF_BookMarkWidget \
    Ui/CCPDF_SearchWidget \
    Ui/CCPDF_LinkWidget \
    Ui/Plugins/Translations \
    External

SOURCES += Core/CCPDFView_Loader/ccpdf_loader.cpp \
    Core/CCPDF_ArgPraser/ccpdf_argpraser.cpp \
    Core/CCPDF_GragRecorder/ccpdf_gragpointrecorder.cpp \
    Core/CCPDF_Historical/FileRecord/ccpdf_historicalrecordhelper.cpp \
    Core/CCPDF_Historical/Historical/historical_record.cpp \
    Core/CCPDF_Info/ccpdf_info.cpp \
    Core/CCPDF_MainView/ccpdf_mainviewwidget.cpp \
    Core/CCPDF_PDFPageNavigator/ccpdf_pdfpagenavigator.cpp \
    Core/CCPDF_PdfServer/ccpdf_pdfserver.cpp \
    Core/CCPDF_PdfView/ccpdf_mypdfview.cpp \
    Core/CCPDF_SelectionRecorder/ccpdf_selectionrecorder.cpp \
    Core/CCPDF_SinglePDF_Component/ccpdf_singlepdf_widget.cpp \
    Core/CCPDF_TextHelper/ccpdf_texthelper.cpp \
    Core/CCPDF_Utils/ccpdf_fileutils.cpp \
    Core/CCPDF_Utils/ccpdf_messgaeboxutils.cpp \
    Core/CCPDF_ZoomController/ccpdf_zoomcontroller.cpp \
    External/DLLSupport/CCPDF_DLLPluginImporter/ccpdf_externalplugin_externeldll_importer.cpp \
    External/External_Option_Compile/CCPDF_RunPluginProcess/ccpdf_runpluginprocess.cpp \
    External/ccpdf_externalplugins.cpp \
    Ui/ActionMonitor/KeyboardMonitor/keyboardmonitor.cpp \
    Ui/ActionMonitor/MouseMonitor/mousemonitor.cpp \
    Ui/ActionMonitor/eventhandlefunctor.cpp \
    Ui/CCPDF_Animanations/ccpdf_animanations.cpp \
    Ui/CCPDF_BookLibraryManager/FileSystemModel/ccpdf_booklirabry_filesystemmodel.cpp \
    Ui/CCPDF_BookLibraryManager/ccpdf_booklibrarymanager.cpp \
    Ui/CCPDF_BookLibraryWidget/ccpdf_booklibrarywidget.cpp \
    Ui/CCPDF_BookMarkManager/BookMarkModel/ccpdf_bookmarkmodel.cpp \
    Ui/CCPDF_BookMarkManager/ccpdf_bookmarkmanager.cpp \
    Ui/CCPDF_BookMarkWidget/ccpdf_bookmarkwidget.cpp \
    Ui/CCPDF_HelpWindow/ccpdf_helpwindow.cpp \
    Ui/CCPDF_HistoryAction/ccpdf_historyaction.cpp \
    Ui/CCPDF_HistoryActionHelper/ccpdf_history_actionhelper.cpp \
    Ui/CCPDF_HistoryTableWidgetContorller/ccpdf_historytablewidgetcontroller.cpp \
    Ui/CCPDF_LinkListWidgetManager/ccpdf_pdflinkwidgetmanager.cpp \
    Ui/CCPDF_LinkWidget/ccpdf_linkwidget.cpp \
    Ui/CCPDF_MdiSubWindow/ccpdf_mdisubwindow.cpp \
    Ui/CCPDF_SearchDelegate/CCPDF_SearchDelegate.cpp \
    Ui/CCPDF_SearchManager/ccpdf_searchmanager.cpp \
    Ui/CCPDF_SearchWidget/ccpdf_searchwidget.cpp \
    Ui/CCPDF_ThemeAction/ccpdf_theme_action.cpp \
    Ui/CCPDF_ThemeActionHelper/ccpdf_themeactionhelper.cpp \
    Ui/MainWindow/ccpdfview_mainwindow.cpp \
    Main/main.cpp \
    Ui/Plugins/OCR/plugin_ocr_uiwidget.cpp \
    Ui/Plugins/Translations/ccpdf_translationwidget.cpp \
    Ui/ThemeController/ccpdf_themecontroller.cpp \
    Ui/WindowBuild/CCPDF_HelpingBuild/ccpdf_helpingbuildhelper.cpp \
    Ui/WindowBuild/CCPDF_ToolBarConfigure/ccpdf_toolbarconfigure.cpp \
    Ui/WindowEventHelper/windoweventhelper.cpp \
    Ui/CCPDF_MdiArea/ccpdf_mdiarea.cpp \

HEADERS += CCPDF_Global.h \
    Core/CCPDFView_Loader/ccpdf_loader.h \
    Core/CCPDF_About/CCPDF_About.h \
    Core/CCPDF_ArgPraser/ccpdf_argpraser.h \
    Core/CCPDF_Error_Helper/CCPDF_ErrorHelper.h \
    Core/CCPDF_GragRecorder/ccpdf_gragpointrecorder.h \
    Core/CCPDF_Historical/FileRecord/ccpdf_historicalrecordhelper.h \
    Core/CCPDF_Historical/Historical/historical_record.h \
    Core/CCPDF_Info/ccpdf_info.h \
    Core/CCPDF_MainView/ccpdf_mainviewwidget.h \
    Core/CCPDF_PDFPageNavigator/ccpdf_pdfpagenavigator.h \
    Core/CCPDF_PdfServer/ccpdf_pdfserver.h \
    Core/CCPDF_PdfView/ccpdf_mypdfview.h \
    Core/CCPDF_SelectionRecorder/ccpdf_selectionrecorder.h \
    Core/CCPDF_SinglePDF_Component/ccpdf_singlepdf_widget.h \
    Core/CCPDF_TextHelper/ccpdf_texthelper.h \
    Core/CCPDF_Utils/CCPDF_StringParseUtil.h \
    Core/CCPDF_Utils/ccpdf_fileutils.h \
    Core/CCPDF_Utils/ccpdf_messgaeboxutils.h \
    Core/CCPDF_ZoomController/ccpdf_zoomcontroller.h \
    Debugging/Debug/CCPDF_Debug_Options.h \
    External/CCPDF_Plugin_Supports.h \
    External/DLLSupport/CCPDF_DLLPluginImporter/ccpdf_externalplugin_externeldll_importer.h \
    External/External_Option_Compile/CCPDF_RunPluginProcess/ccpdf_runpluginprocess.h \
    External/ccpdf_externalplugins.h \
    Ui/ActionMonitor/KeyboardMonitor/keyboardmonitor.h \
    Ui/ActionMonitor/MouseMonitor/mousemonitor.h \
    Ui/ActionMonitor/eventhandlefunctor.h \
    Ui/CCPDF_Animanations/ccpdf_animanations.h \
    Ui/CCPDF_BookLibraryManager/FileSystemModel/ccpdf_booklirabry_filesystemmodel.h \
    Ui/CCPDF_BookLibraryManager/ccpdf_booklibrarymanager.h \
    Ui/CCPDF_BookLibraryWidget/ccpdf_booklibrarywidget.h \
    Ui/CCPDF_BookMarkManager/BookMarkModel/ccpdf_bookmarkmodel.h \
    Ui/CCPDF_BookMarkManager/ccpdf_bookmarkmanager.h \
    Ui/CCPDF_BookMarkWidget/ccpdf_bookmarkwidget.h \
    Ui/CCPDF_HelpWindow/ccpdf_helpwindow.h \
    Ui/CCPDF_HistoryAction/ccpdf_historyaction.h \
    Ui/CCPDF_HistoryActionHelper/ccpdf_history_actionhelper.h \
    Ui/CCPDF_HistoryTableWidgetContorller/ccpdf_historytablewidgetcontroller.h \
    Ui/CCPDF_LinkListWidgetManager/ccpdf_pdflinkwidgetmanager.h \
    Ui/CCPDF_LinkWidget/ccpdf_linkwidget.h \
    Ui/CCPDF_MdiSubWindow/ccpdf_mdisubwindow.h \
    Ui/CCPDF_SearchDelegate/CCPDF_SearchDelegate.h \
    Ui/CCPDF_SearchManager/ccpdf_searchmanager.h \
    Ui/CCPDF_SearchWidget/ccpdf_searchwidget.h \
    Ui/CCPDF_ThemeAction/ccpdf_theme_action.h \
    Ui/CCPDF_ThemeActionHelper/ccpdf_themeactionhelper.h \
    Ui/MainWindow/ccpdfview_mainwindow.h \
    Ui/Plugins/OCR/plugin_ocr_uiwidget.h \
    Ui/Plugins/Translations/ccpdf_translationwidget.h \
    Ui/ThemeController/ccpdf_themecontroller.h \
    Ui/WindowBuild/CCPDF_HelpingBuild/ccpdf_helpingbuildhelper.h \
    Ui/WindowBuild/CCPDF_ToolBarConfigure/ccpdf_toolbarconfigure.h \
    Ui/WindowEventHelper/windoweventhelper.h \
    Ui/CCPDF_MdiArea/ccpdf_mdiarea.h \


FORMS += \
    Ui/CCPDF_BookLibraryWidget/ccpdf_booklibrarywidget.ui \
    Ui/CCPDF_BookMarkWidget/ccpdf_bookmarkwidget.ui \
    Ui/CCPDF_HelpWindow/ccpdf_helpwindow.ui \
    Ui/CCPDF_LinkWidget/ccpdf_linkwidget.ui \
    Ui/CCPDF_SearchWidget/ccpdf_searchwidget.ui \
    Ui/MainWindow/ccpdfview_mainwindow.ui \
    Ui/Plugins/OCR/plugin_ocr_uiwidget.ui \
    Ui/Plugins/Translations/ccpdf_translationwidget.ui

# Markings
# You can compile for your specifies
# SUPPORT_TRANSLATION: Enable Translations Plugin Supports
# SUPPORT_TESS_OCR: Support Tesseract OCR's Dynamic Loader, required TessractWrapper.dll


DEFINES += \ # CHECK_MEMORY \
           SUPPORT_TESS_OCR \
           SUPPORT_TRANSLATION \
           PURE_RELEASE


DEFINES +=  __MAJOR_VERSION=1 \
            __MINOR_VERISON=0

CONFIG (release, debug|release) {
    contains(DEFINES, PURE_RELEASE){
        DEFINES += QT_NO_WARNING_OUTPUT
        DEFINES += QT_NO_DEBUG_OUTPUT
    }
}

contains(DEFINES, SUPPORT_TESS_OCR){
HEADERS +=  \
            External/Internal_Option_Compile/ocr/ccpdf_ocrtexthellper.hpp \
            External/Internal_Option_Compile/ocr/ocranalisishelper.h \
            Ui/Plugins/OCR/plugin_ocruimanager.h \


SOURCES +=  \
            External/Internal_Option_Compile/ocr/ocranalisishelper.cpp \
            Ui/Plugins/OCR/plugin_ocruimanager.cpp \

}

contains(DEFINES, SUPPORT_TRANSLATION){
HEADERS +=  \
    External/External_Option_Compile/CCPDF_ExternTranslations/Translate/ccpdf_externtranslation.h \

SOURCES +=  \
            External/External_Option_Compile/CCPDF_ExternTranslations/Translate/ccpdf_externtranslation.cpp \

}

# Documentations Install
DEFINES += DocDir=\\\"./Documentation/\\\"

COPY_DIR = $$PWD/Documentation/
COPY_FILES.files = $$COPY_DIR/About.md \
                   $$COPY_DIR/Browse_PDF.md \
                   $$COPY_DIR/Historical.md \
                   $$COPY_DIR/Library.md \
                   $$COPY_DIR/LoadPDF.md \
                   $$COPY_DIR/PDF_Link.md \
                   $$COPY_DIR/Plugin_OCR.md \
                   $$COPY_DIR/Plugin_Translations.md \
                   $$COPY_DIR/Searching.md \
                   $$COPY_DIR/SwitchThemes.md \
                   $$COPY_DIR/TextGrabber.md \
                   $$COPY_DIR/Help.md \
                   $$COPY_DIR/Key_Sequences.md

COPY_FILES.path = Documentation/

COPIES += COPY_FILES

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources/configs.qrc
