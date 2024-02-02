#include "pdf_historicalrecord.h"
#include "PDF_Utils.h"
#include "notehandle.h"

bool PDF_HistoricalRecord::isPathIndicatesPDF(QString path)
{
    return path.endsWith(".pdf");
}

PDF_HistoricalRecord::PDF_HistoricalRecord()
{
    setHistFilePath();
    setBookModelDirPath();
}

void PDF_HistoricalRecord::addHistFile(QString path, int index)
{
    historyFileNames.push_back(path);
    pdfIndexLists.push_back(index);
}

bool PDF_HistoricalRecord::removeHist(QString path)
{
    int     index = historyFileNames.indexOf(path);
    bool    st1 =   historyFileNames.removeOne(path);
    if(index == -1 || index >= path.size())
        return st1;
    pdfIndexLists.removeAt(index);
    return st1;
}

bool PDF_HistoricalRecord::updateFileIndex(QString path, int newIndex)
{
    int index = historyFileNames.indexOf(path);
    if(index == -1)
        return false;
    pdfIndexLists[index] = newIndex;
    return true;
}

int PDF_HistoricalRecord::getIndex(QString path){
    int index = historyFileNames.indexOf(path);
    if(index == -1)
        return 0;
    return pdfIndexLists[index];
}

void PDF_HistoricalRecord::clearHist()
{
    historyFileNames.clear();
    pdfIndexLists.clear();
}

NoteHandle* PDF_HistoricalRecord::configNoteHandle()
{
    NoteHandle* handle = new NoteHandle;
    readNoteTypehandle(handle);
    return handle;
}


void PDF_HistoricalRecord::recordNotehandle(NoteHandle* handle)
{
    writeNoteTypehandle(handle);
}


bool PDF_HistoricalRecord::setNoteBook(QString pdf, QString noteBookPath, bool cover)
{
    if(!cover && noteMap.contains(pdf)){
        return false;
    }
    noteMap.insert(pdf, noteBookPath);
    return true;
}

QString PDF_HistoricalRecord::getNoteBook(QString pdfPath)
{
    return noteMap.value(pdfPath);
}

bool PDF_HistoricalRecord::hasNoteBook(QString pdf)
{
    return noteMap.keys().contains(pdf);
}

void PDF_HistoricalRecord::removeNoteBook(QString pdf)
{
    noteMap.remove(pdf);
}

bool PDF_HistoricalRecord::readRequired()
{
    bool st1 = readHist();
    bool st2 = readOCR();
    bool st3 = readNote();
    bool st4 = readTheme();
    return st1 && st2 && st3 && st4;
}

bool PDF_HistoricalRecord::writeRequired()
{
    clearFiles();
    bool st1 = writeHist();
    bool st2 = writeOCR();
    bool st3 = writeNote();
    bool st4 = writeTheme();
    return st1 && st2 && st3 && st4;
}

bool PDF_HistoricalRecord::readHist()
{
    bool state = false;
    this->historyFileNames = PDFWindowDataUtils_ReadWriteFile::getDatasFromFile(histFilePath, state);
    this->bookmodelPath = PDFWindowDataUtils_ReadWriteFile::getDataFromFile(bookModelHistFilePath, state);
    this->pdfIndexLists = PDFWindowDataUtils_ReadWriteFile::getIndexFromFile(pdfIndexFilePath, state);
    if(pdfIndexLists.size() < historyFileNames.size())
    {
        pdfIndexLists.clear();
        for(int i = 0; i < historyFileNames.size(); i++)
            pdfIndexLists.push_back(0);
    }
    return state;
}

bool PDF_HistoricalRecord::readOCR()
{
    bool state = false;
    QStringList tmp = PDFWindowDataUtils_ReadWriteFile::getDatasFromFile(ocrConfigFilePath, state);
    if(state || tmp.size() != 3)
        return false;

    this->OCR_exePath = tmp[0];
    this->OCR_ImageDir = tmp[1];
    this->OCR_ResDor = tmp[2];
    return true;
}

bool PDF_HistoricalRecord::readNote()
{
    bool state = false;
    QStringList eachRecord = PDFWindowDataUtils_ReadWriteFile::getDatasFromFile(noteBooksRecorderPath, state);
    if(!state)
        return false;

    for(auto& each : eachRecord)
    {
        QStringList eachSplit = each.split(NoteSeperator);
        if(eachSplit.size() < 2)
            continue;
        this->noteMap.insert(eachSplit[0], eachSplit[1]);
    }
    return true;
}

bool PDF_HistoricalRecord::readTheme()
{
    bool state = false;
    QList<int> t= PDFWindowDataUtils_ReadWriteFile::getIndexFromFile(themeFileHandle, state);
    if(t.size() != 1)
        themeIndex = 0;
    else
        themeIndex = t[0];
    return true;
}

bool PDF_HistoricalRecord::readNoteTypehandle(NoteHandle* n)
{
    bool state = false;
    QStringList maps = PDFWindowDataUtils_ReadWriteFile::getDatasFromFile(TypehandleHistFilePath, state);
    if(!state)
        return false;
    for(auto& each : maps)
    {
        QStringList eachSplit = each.split(noteTypeSeperator);
        if(eachSplit.size() < 2)
            continue;
        // type || exe
        n->setHandler(eachSplit[0], eachSplit[1]);
    }
    return true;
}


bool PDF_HistoricalRecord::writeHist()
{
    bool st1 = PDFWindowDataUtils_ReadWriteFile::writeDataToFile(bookModelHistFilePath, this->bookmodelPath);
    bool st2 = PDFWindowDataUtils_ReadWriteFile::writeDatasToFile(histFilePath, this->historyFileNames);
    bool st3 = PDFWindowDataUtils_ReadWriteFile::writeIndexs(pdfIndexFilePath, this->pdfIndexLists);
    return st1 && st2 && st3;
}

bool PDF_HistoricalRecord::writeOCR()
{
    QStringList l;
    l << this->OCR_exePath << this->OCR_ImageDir << this->OCR_ResDor;
    PDFWindowDataUtils_ReadWriteFile::writeDatasToFile(ocrConfigFilePath, l);
    return true;
}

bool PDF_HistoricalRecord::writeNote()
{
    auto it = this->noteMap.cbegin();
    QStringList records;
    while(it != this->noteMap.cend())
    {
        records << it.key() + NoteSeperator + it.value();
        it++;
    }
    PDFWindowDataUtils_ReadWriteFile::writeDatasToFile(noteBooksRecorderPath, records);
    return true;
}

bool PDF_HistoricalRecord::writeTheme()
{
    QList<int> th;
    th << this->themeIndex;
    PDFWindowDataUtils_ReadWriteFile::writeIndexs(themeFileHandle, th);
    return true;
}

bool PDF_HistoricalRecord::writeNoteTypehandle(NoteHandle* n)
{
    auto map = n->getMap();
    auto it = map.cbegin();
    QStringList records;
    while(it != map.cend())
    {
        // type || exe
        records << it.key() + noteTypeSeperator + it.value();
        it++;
    }
    PDFWindowDataUtils_ReadWriteFile::writeDatasToFile(TypehandleHistFilePath, records);
    return true;
}

void PDF_HistoricalRecord::clearFiles()
{
    PDFWindowDataUtils_ReadWriteFile::clearFiles(histFilePath);
    PDFWindowDataUtils_ReadWriteFile::clearFiles(bookmodelPath);
    PDFWindowDataUtils_ReadWriteFile::clearFiles(pdfIndexFilePath);
    PDFWindowDataUtils_ReadWriteFile::clearFiles(ocrConfigFilePath);
    PDFWindowDataUtils_ReadWriteFile::clearFiles(themeFileHandle);
}
