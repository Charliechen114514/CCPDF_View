#ifndef PDF_EXPORTPDFEX_H
#define PDF_EXPORTPDFEX_H

#include "PDF_Utils.h"
#include <QObject>
#include <QThread>
class PDF_ExportPDFEx;
class QPdfDocument;
class PDF_ExportThread;
class QPdfWriter;
class PDF_WorkerBase : public QThread
{
    Q_OBJECT
public:
    PDF_WorkerBase() = default;
    virtual ~PDF_WorkerBase() = default;
    Q_DISABLE_COPY(PDF_WorkerBase);
    void setStopImm(){shellStop = true;};
    virtual void run() = 0;
protected:
    bool shellStop = false;
};

class PDF_RenderThread : public PDF_WorkerBase
{
    Q_OBJECT
public:
    const int waiting_sec = 1;
    const int acceptable_pic = 25;
    friend class PDF_ExportPDFEx;
    PDF_RenderThread() = delete;
    Q_DISABLE_COPY(PDF_RenderThread);
    explicit PDF_RenderThread(QPdfDocument* ex, PDF_ExportThread* who, QMap<int, QImage*>* editedOne);
    ~PDF_RenderThread(){
        this->quit();
        this->wait();
    }
    void    run() override;
    void    renderPic(int pg);
    bool    required_sleep(int pg);
signals:
    void    startRender();
    void    startRenderIndex(int index);
    void    finishRender();
private:
    QPdfDocument*           handle_doc      = nullptr;
    QMap<int, QImage*>*     editedOne       = nullptr;
    PDF_ExportThread*       exportWorker    = nullptr;
    PDF_ExportWriterConfig  conf;
};

class PDF_ExportThread : public PDF_WorkerBase
{
    Q_OBJECT
public:
    friend class PDF_ExportPDFEx;
    friend class PDF_RenderThread;
    const int waiting_second = 1;
    PDF_ExportThread() = delete;
    Q_DISABLE_COPY(PDF_ExportThread);
    ~PDF_ExportThread() override;
    explicit PDF_ExportThread(QString exportPath);
    void    run() override;
    void    setTolPage(int pg){totalPage = pg;}
    void    exportRequired(QImage* image, bool required_newpage, QPainter &p, QPdfWriter *w);

signals:
    void    startExport();
    void    startExportIndex(int index);
    void    finishExport();
private:
    QList<QImage*>          required_export;
    QString                 exportPath;
    int                     totalPage = 0;
    int                     curHandlePage = 0;
    void                    handleQuit();
};


class PDF_ExportPDFEx : public QObject
{
    Q_OBJECT
public:
    explicit PDF_ExportPDFEx(QPdfDocument* doc,QString path,
                             QMap<int, QImage*>* editedOne, QObject *parent = nullptr);
    ~PDF_ExportPDFEx() override;
    PDF_ExportPDFEx() = delete;
    Q_DISABLE_COPY(PDF_ExportPDFEx);
    bool                isWorkingCurrent();
    void                cancelAll();
    void                startWork();

signals:
    // Thread transpass signals
    void                startRender();
    void                startRenderIndex(int index);
    void                finishRender();
    void                startExport();
    void                startExportIndex(int index);
    void                finishExport();
    void                cancelFinish();
private:
    PDF_RenderThread*   renderThread    = nullptr;
    PDF_ExportThread*   exportThread    = nullptr;
    bool                isCancelExportLeaveTheRest = false;
    void                initConnections();
    void                configRenderThread(QPdfDocument* doc, QMap<int, QImage*>* editedOne);
    void                configExportThread(QString path);
    void                cleanRenderThread();
};

#endif // PDF_EXPORTPDFEX_H
