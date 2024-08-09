#ifndef CCPDF_DEBUG_OPTIONS_H
#define CCPDF_DEBUG_OPTIONS_H
#ifdef CHECK_MEMORY
#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) ||  \
    defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32__) || defined(__NT__)
#include <vld.h>
#endif
#endif
#endif  // CCPDF_DEBUG_OPTIONS_H
