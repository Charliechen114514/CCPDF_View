#ifndef OCRERRORSTRINGADAPTER_H
#define OCRERRORSTRINGADAPTER_H
#include "ocrpackage.h"
#include "ocrpackageprivate.h"
class OCRErrorStringAdapter
{
public:
    static QString makeString(OCRPackage::ErrorState state){
        switch(state)
        {
        case OCRPackage::ErrorState::NO_ERROR:
            return "No error in current";
        case OCRPackage::ErrorState::CORE_UNINITED:
            return "Core not inited";
        case OCRPackage::ErrorState::NO_OCR_EXE_PATH:
            return "OCR's (example: Tesseract.exe)'s path is not set correctly";
        case OCRPackage::ErrorState::NO_SAVING_DIR_PATH:
            return "OCR's saving dir is error! check the saving dir for a stable and expected output";
        case OCRPackage::ErrorState::NO_TASK_BUT_START:
            return "NO pictures is waiting to detected, no mission depatch!";
        case OCRPackage::ErrorState::TASK_ALREADY_DEPATCH:
            return "IS Processing! do not start again!";
        case OCRPackage::ErrorState::Unknown_Error:
            return "Unknown error";
        }
        return "Unknown error";
    }
};

class OCR_ErrorAdapter
{
public:
    static OCRPackage::ErrorState AdaptionOfError(OCRPackagePrivate::ErrorState state){
        switch(state)
        {
        case OCRPackagePrivate::ErrorState::NO_ERROR:
            return OCRPackage::ErrorState::Unknown_Error;
            break;
        case OCRPackagePrivate::ErrorState::NO_EXECUTABLE:
            return OCRPackage::ErrorState::NO_OCR_EXE_PATH;
            break;
        case OCRPackagePrivate::ErrorState::NO_SAVING_DIR:
            return OCRPackage::ErrorState::NO_SAVING_DIR_PATH;
            break;
        case OCRPackagePrivate::ErrorState::EMPTY_TASK:
            return OCRPackage::ErrorState::NO_TASK_BUT_START;
            break;
        case OCRPackagePrivate::ErrorState::TASK_ALREADY_DEPATCH:
            return OCRPackage::ErrorState::TASK_ALREADY_DEPATCH;
            break;
        }
        return OCRPackage::ErrorState::Unknown_Error;
    }
};


#endif // OCRERRORSTRINGADAPTER_H
