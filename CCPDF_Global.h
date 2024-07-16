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





// Zoom Params Define
namespace INIT_PARAMS
{
    static constexpr    double  ZOOM_INIT           = 1.0;
    static constexpr    bool    HYPER_WID_VISIBLE   = false;
    static constexpr    bool    BOOKMODEL_VISIBLE   = false;
    static constexpr    bool    SELECTION_VISIBLE   = false;
};


#endif // CCPDF_GLOBAL_H
