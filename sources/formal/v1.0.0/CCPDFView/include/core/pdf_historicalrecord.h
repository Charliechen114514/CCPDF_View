#ifndef PDF_HISTORICALRECORD_H
#define PDF_HISTORICALRECORD_H
#include <QStringList>
#include <QMap>
#include "PDF_PathSettings.h"
class NoteHandle;

class PDF_HistoricalRecord
{
public:
    PDF_HistoricalRecord();
    PDF_HistoricalRecord(const PDF_HistoricalRecord&) = delete;
    const PDF_HistoricalRecord& operator=(const PDF_HistoricalRecord&) = delete;

    static bool     isPathIndicatesPDF(QString path);

    void            setHistFilePath(QString path = HISTORY_RECORD_FILE_PATH){histFilePath = path;}
    void            setBookModelDirPath(QString path = BOOK_MODEL_DIR_PATH){bookModelHistFilePath = path;}
    void            setPdfIndexFilePath(QString path = PDF_IDNEX_HIST_FILE_PATH){pdfIndexFilePath = path;}
    QString         getBookModelDirPath(){return this->bookmodelPath;}
    QString         getHistFilePath(){return histFilePath;}
    QString         getPdfIndexFilePath(){return this->pdfIndexFilePath;}

    // set get the res
    void            setHistoryFilePaths(QStringList& l){historyFileNames = l;}
    void            setBookModeFileDirPath(QString l){bookmodelPath = l;}
    void            setOCREXE(QString path){this->OCR_exePath = path;}
    void            setOCRImageDir(QString path){this->OCR_ImageDir = path;}
    void            setOCRResDir(QString path){this->OCR_ResDor = path;}

    QStringList&    getHistoryFilePaths(){return historyFileNames;}
    QString&        getBookModeFileDirPath(){return this->bookmodelPath;}
    QList<int>&     getPdfIndexLists(){return this->pdfIndexLists;}
    QString&        getOCREXE(){return this->OCR_exePath;}
    QString&        getOCRImageDir(){return this->OCR_ImageDir;}
    QString&        getOCRResDir(){return this->OCR_ResDor;}


    // enRecord deRecord
    void            addHistFile(QString path, int index);
    bool            removeHist(QString path);
    bool            updateFileIndex(QString path, int newIndex);
    int             getIndex(QString path);
    void            clearHist();

    // notebook handles
    NoteHandle*     configNoteHandle();
    void            recordNotehandle(NoteHandle* handle);
    // notes
    bool            setNoteBook(QString pdf, QString noteBookPath, bool cover);
    QString         getNoteBook(QString pdfPath);
    bool            hasNoteBook(QString pdf);
    void            removeNoteBook(QString pdf);

    // themes
    void            setThemeIndex(int index){themeIndex = index;};
    int             getThemeIndex(){return themeIndex;};

    bool            readRequired();
    bool            writeRequired();

    void            clearFiles();



private:
    using           FileRecoderType = QString;
    FileRecoderType histFilePath = HISTORY_RECORD_FILE_PATH;
    FileRecoderType bookModelHistFilePath =  BOOK_MODEL_DIR_PATH;; // For FileSystemModel (PDFView::BookMarketMode)
    FileRecoderType pdfIndexFilePath = PDF_IDNEX_HIST_FILE_PATH;
    FileRecoderType noteBooksRecorderPath = PDF_Notes_FILE_PATH;
    FileRecoderType TypehandleHistFilePath = PDF_TYPE_HANDLE_FILE_PATH;
    FileRecoderType themeFileHandle = THEME_HANDLE_FILE_PATH;
    QString         bookmodelPath; // fetch from the bookModelHistFilePath
    QStringList     historyFileNames;
    QList<int>      pdfIndexLists;

    using           PDFFilePath = QString;
    using           NoteBookFilePath = QString;
    using           NoteMap = QMap<PDFFilePath, NoteBookFilePath>;
    const QString   NoteSeperator = "||";
    const QString   noteTypeSeperator = "||";
    NoteMap         noteMap;
    QString         ocrConfigFilePath = OCR_CONFIG_PATH;
    // subRead
    bool            readHist();
    bool            readOCR();
    bool            readNote();
    bool            readNoteTypehandle(NoteHandle* n);
    bool            readTheme();
    bool            writeHist();
    bool            writeOCR();
    bool            writeNote();
    bool            writeTheme();
    bool            writeNoteTypehandle(NoteHandle* n);
    QString         OCR_exePath = OCR_EXE_PATH;
    QString         OCR_ImageDir = IMAGE_SAVE_DIR_PATH;
    QString         OCR_ResDor = TEXT_SAVE_DIR_PATH;
    int             themeIndex;
};

#endif // PDF_HISTORICALRECORD_H
