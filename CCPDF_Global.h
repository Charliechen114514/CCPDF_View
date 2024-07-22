#ifndef CCPDF_GLOBAL_H
#define CCPDF_GLOBAL_H
// Global File Includes
#include <QStringList>
// Quick Develop
// I know Qt owns Disable copying... but I'd rather write my own lol
#define DISABLE_COPY(className) \
    className(const className&) = delete; \
    const className& operator=(const className&) = delete

// Marks
// Memory Marks
#define __MEMEROY_HOLD_BY_OBJ_TREE
#define __MEMEROY_HOLD_BY_SMT_PTR
#define __MEMEROY_NO_HOLD
#define __MEMORY_PASS_NEW_ONLY

// Kind Of Slots
#define __BIND_Ui_Widgets   inline
#define __BIND_Ui_No_Inline

// Logging helper
#define __DEF_LOG_PDF_REC       "./logging/pdf_record.json"
#define __DEF_PLUGIN_PDF_LOG    "./logging/plugin_record.json"
#define __DEF_OTHER_SERVER_LOG  "./logging/other_server.json"
#define __DEF_THEME_INITIALIZE  "./logging/theme_record.json"
// Communicate with Single Widget
#define __COM_SIG_WIDGET

// External Macro
#define __Required_Static_Cast_For_Further_Using

// External Sources
#define __PLUGIN
#define __PLUGIN_SHARE      QString("./plugin/share/")
#define __OCR_SHARE_PIC     __PLUGIN_SHARE + "ocr_image"

#define __DocDir            DocDir


// Platforms Related
#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define WINDOWS
#endif

// Zoom Params Define
namespace INIT_PARAMS
{
    static constexpr    double  ZOOM_INIT[[maybe_unused]]           = 1.0;
    static constexpr    bool    HYPER_WID_VISIBLE[[maybe_unused]]   = false;
    static constexpr    bool    BOOKMODEL_VISIBLE[[maybe_unused]]   = false;
    static constexpr    bool    SELECTION_VISIBLE[[maybe_unused]]   = false;
    static constexpr    bool    TOOLBAR_VISIBLE[[maybe_unused]]     = true;
    static constexpr    bool    MDISUB_VISIBLE[[maybe_unused]]      = true;
};


#endif // CCPDF_GLOBAL_H
