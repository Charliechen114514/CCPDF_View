#include "ccspeech_core.h"
#include <QTextToSpeech>

CCSpeech_Core::CCSpeech_Core() {
    _init();
}

void CCSpeech_Core::_init() {
    speechCore = std::make_shared<QTextToSpeech>();
}

void CCSpeech_Core::switch_engine(const QString& each) {
    if (each == Configure::DEFAULT_ST) {
        speechCore.reset(new QTextToSpeech());
    } else {
        speechCore.reset(new QTextToSpeech(each));
    }
}
