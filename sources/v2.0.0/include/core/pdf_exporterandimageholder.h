#ifndef PDF_EXPORTERANDIMAGEHOLDER_H
#define PDF_EXPORTERANDIMAGEHOLDER_H
#include <QThread>
#include <QObject>
#include <QMap>
class QPdfDocument;
class PDF_ExporterAndImageHolder;
class RenderWorker : public QThread
{
    Q_OBJECT
public:
    RenderWorker() = delete;
    RenderWorker(const RenderWorker*) = delete;
    const RenderWorker* operator=(const RenderWorker*) = delete;
    RenderWorker(QPdfDocument* doc,PDF_ExporterAndImageHolder* manager, QObject* parent = nullptr);
    virtual         ~RenderWorker();
    QPdfDocument*   getDocumentRenderHolding(){return doc;}
    void            run()override;
    void            setStopImm(){shellStop = true;};
signals:

    void startRender();
    void finishRenderIndex(int pg);
    void finishRenderAll();

    void errorOccur();

private:
    void                            renderTaskCore();
    PDF_ExporterAndImageHolder*     manager;
    QPdfDocument*                   doc;
    bool                            shellStop = false;
};

class ExportWorker : public QThread
{
    Q_OBJECT;
public:
    ExportWorker() = delete;
    ExportWorker(const ExportWorker&) = delete;
    const ExportWorker& operator=(const ExportWorker&) = delete;
    ExportWorker(const QString path, PDF_ExporterAndImageHolder* manager, QObject* parent = nullptr);
    virtual ~ExportWorker();
    void run()override;

    void    setStopImm(){shellStop = true;};

signals:

    void                            startExport();
    void                            finishExportPg(int pg);
    void                            finishExport();

    void                            errorOccur();

private:
    void                            exportTaskCore();
    QString                         exportPath;
    PDF_ExporterAndImageHolder*     manager;
    bool                            shellStop = false;
};



class PDF_ExporterAndImageHolder : public QObject
{
    Q_OBJECT
public:
    enum class Error
    {
        RENDER_UNSET,
        EXPORT_ERROR,

        NO_ERROR
    };
    explicit PDF_ExporterAndImageHolder(QPdfDocument* doc, QObject *parent = nullptr);
    PDF_ExporterAndImageHolder() = delete;
    PDF_ExporterAndImageHolder(const PDF_ExporterAndImageHolder&) = delete;
    const PDF_ExporterAndImageHolder& operator=(const PDF_ExporterAndImageHolder&) = delete;
    virtual ~PDF_ExporterAndImageHolder();
    void                            setDocument(QPdfDocument* doc){currentHandleDoc = doc;}
    QPdfDocument*                   getDoc(){return currentHandleDoc;}
    void                            registerTheEdited(QMap<int, QImage *> *s);
    void                            setExportPath(QString path);
    QString                         getExportPath(){return exportPath;}
    bool                            isExportingCurrent();
    bool                            isAcssessbleForRenderWork();
    bool                            isAcssessbleForExportWork();

    void                            doAllWorkOneByOne();
    void                            startRenderWork();
    void                            startExportWork();
    Error                           getError(){return err;}
    void                            restartForRenderWork(QPdfDocument *doc);
    void                            cancelAll();
    void                            setAutoDelIfCancel(bool st){isCancelExportLeaveTheRest = st;}
signals:
    // render
    void                            startRender();
    void                            finishRenderIndex(int pg);
    void                            finishRenderAll();

    // export
    void                            startExport();
    void                            finishExportPg(int pg);
    void                            finishExport();
    void                            cancelFinish();

    void                            startExportImm();
private slots:

    void                            handleTheRenderPartialFinish(int pg);
    void                            handleTheRenderFinish();
    void                            handleTheExportPartialFinish(int pg);
    void                            handleTheExportFinish();
private:
    friend class RenderWorker;
    friend class ExportWorker;
    Error                           err = Error::NO_ERROR;
    QPdfDocument*                   currentHandleDoc = nullptr;
    QString                         exportPath;
    RenderWorker*                   renderWorker; // handle the render task
    ExportWorker*                   exportWorker; // handle the export Mission
    QList<QImage*>                  renderResults;
    QMap<int, QImage*>*             editedOne;
    bool                            isExportable = false;
    bool                            shallExportImm = false;
    bool                            isCancelExportLeaveTheRest = false;
    void                            setExportableAfterRender(){isExportable = true;}
    void                            initConnectionRender();
    void                            initConnectionExport();
    void                            setError(Error e){err = e;}
    void                            clearError(){err = Error::NO_ERROR;}
    void                            createRenderThread();
    void                            createExporterThread();
    void                            releaseThreads();
    void                            releaseRenderThread();
    void                            releaseExporterThread();
    void                            releaseRenderSources();

};

#endif // PDF_EXPORTERANDIMAGEHOLDER_H
