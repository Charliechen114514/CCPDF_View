#ifndef PDF_FILEVIEWMANAGER_H
#define PDF_FILEVIEWMANAGER_H
#include <QStringList>
#include <QTableWidgetItem>
class PDF_FileViewManager
{
public:
    const short DefaultRowCount = 2;
    using FileNameWidget = QTableWidgetItem;
    using FilePathWidget = QTableWidgetItem;
    PDF_FileViewManager(QTableWidget* w);
    PDF_FileViewManager(const PDF_FileViewManager&) = delete;
    const PDF_FileViewManager& operator=(const PDF_FileViewManager&) = delete;
    ~PDF_FileViewManager();

    QTableWidget*           getOperatingWidget(){return operatingWidget;}

    void                    configFiles(QStringList l);
    void                    addPath(QString l);
    void                    configTableWidget();
    bool                    isFileExists(QString l);
    void                    removeTarget(QString l);
    void                    removeTarget(FilePathWidget* w);
private:
    using FileMapRecorder = QMap<FilePathWidget*, FileNameWidget*>;
    FileMapRecorder         filePathItems;
    QTableWidget*           operatingWidget = nullptr;
    void                    configWidget(QTableWidgetItem* i);
    void                    clearWidget();
    void                    clearMap();
};

#endif // PDF_FILEVIEWMANAGER_H
