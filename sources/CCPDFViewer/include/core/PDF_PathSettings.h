#ifndef PDF_PATHSETTINGS_H
#define PDF_PATHSETTINGS_H
#ifndef QT_NO_DEBUG
static const char* HISTORY_RECORD_FILE_PATH = "D:/QT projects/CCPDFViewer/WindowInfo/Hist.hist";
static const char* BOOK_MODEL_DIR_PATH = "D:/QT projects/CCPDFViewer/WindowInfo/BookModelDirPath.hist";
static const char* PDF_IDNEX_HIST_FILE_PATH = "D:/QT projects/CCPDFViewer/WindowInfo/PDFIndex.hist";
static const char* PDF_Notes_FILE_PATH = "D:/QT projects/CCPDFViewer/WindowInfo/NoteBookMap.hist";
static const char* PDF_TYPE_HANDLE_FILE_PATH = "D:/QT projects/CCPDFViewer/WindowInfo/NoteHandleHist.hist";
static const char* THEME_HANDLE_FILE_PATH = "D:/QT projects/CCPDFViewer/WindowInfo/ThemeHist.hist";

static const char* OCR_CONFIG_PATH = "D:/QT projects/CCPDFViewer/WindowInfo/OCRConfig.hist";
static const char* IMAGE_SAVE_DIR_PATH = "D:/QT projects/CCPDFViewer/ocr/image/";
static const char* TEXT_SAVE_DIR_PATH = "D:/QT projects/CCPDFViewer/ocr/text/";
static const char* OCR_EXE_PATH = "D:/Tesseract/tesseract.exe";
static const char* EDIT_PDF_SAVING_PATH_DIR = "D:/QT projects/CCPDFViewer/Edited/";
static const char* SENTENCE_POOL_PATH = "D:/QT projects/CCPDFViewer/WindowInfo/Special_Sentence.txt";
static const char* TRANSLATE_EXE_PATH = "";

#else
static const char* HISTORY_RECORD_FILE_PATH = "./WindowInfo/Hist.hist";
static const char* BOOK_MODEL_DIR_PATH = "./WindowInfo/BookModelDirPath.hist";
static const char* PDF_IDNEX_HIST_FILE_PATH = "./WindowInfo/PDFIndex.hist";
static const char* PDF_Notes_FILE_PATH = "./WindowInfo/NoteBookMap.hist";
static const char* PDF_TYPE_HANDLE_FILE_PATH = "./WindowInfo/NoteHandleHist.hist";
static const char* THEME_HANDLE_FILE_PATH = "./WindowInfo/ThemeHist.hist";

static const char* OCR_CONFIG_PATH = "./WindowInfo/OCRConfig.hist";
static const char* IMAGE_SAVE_DIR_PATH = "./ocr/image/";
static const char* TEXT_SAVE_DIR_PATH = "./ocr/text/";
static const char* OCR_EXE_PATH = "./ocr/ocrSource/tesseract.exe";
static const char* EDIT_PDF_SAVING_PATH_DIR = "./Edited/";
static const char* SENTENCE_POOL_PATH = "./WindowInfo/Special_Sentence.txt";
static const char* TRANSLATE_EXE_PATH = "";
#endif
#endif // PDF_PATHSETTINGS_H
