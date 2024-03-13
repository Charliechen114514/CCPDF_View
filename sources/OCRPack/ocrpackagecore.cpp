#include "ocrpackagecore.h"

bool OCRPackageCore::execute(){
    if(this->exePath.isEmpty())
        return false;

    if(!this->processor)
        return false;

    this->processor->execute(exePath, makeArgs());

    return true;
}
