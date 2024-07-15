#ifndef CCPDF_PLUGIN_SUPPORTS_H
#define CCPDF_PLUGIN_SUPPORTS_H

// Plugin Internal Support
#ifdef SUPPORT_TESS_OCR
#define _OCR_TESS "OCR_TESS"
#else
#define _OCR_TESS ""
#endif

#ifdef SUPPORT_TRANSLATION
#define _TRANSLATION "TRANSLATION"
#else
#define _TRANSLATION ""
#endif


#endif // CCPDF_PLUGIN_SUPPORTS_H
