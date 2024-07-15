#ifndef CCPDF_HISTORYTABLEWIDGETCONTROLLER_H
#define CCPDF_HISTORYTABLEWIDGETCONTROLLER_H
#include "CCPDF_Global.h"
#include "CCPDF_Historical/Historical/historical_record.h"
#include <QPoint>
class CCPDFView_MainWindow;
class QTableWidget;
class QTableWidgetItem;
class QMenu;

struct CONTROL_UI_INFO{
    static constexpr unsigned short DEFAULT_COL     = 3;
    static constexpr unsigned short PATH_INDEX      = 0;
    static constexpr unsigned short FILE_NAME_INDEX = 1;
    static constexpr unsigned short PAGE_INDEX      = 2;

    static constexpr const char*    TITLES[DEFAULT_COL]{
        "文件位置",
        "PDF名称",
        "记录页码"
    };
};

class CCPDF_HistoryTableWidgetController : public QObject
{
    Q_OBJECT
public:
    CCPDF_HistoryTableWidgetController() = delete;
    DISABLE_COPY(CCPDF_HistoryTableWidgetController);
    CCPDF_HistoryTableWidgetController(QTableWidget* w, QObject* parent = nullptr);
    void                                    setExecutionPoint(const QPoint &ff);
    void                                    setBindHistLists
                    (const QList<PDF_Info_Historical_Record>& infos);
    bool                                    setFocusingForMenu(QPoint where);
    void                                    doItemClick(QTableWidgetItem *item);
    void                                    doMenuShowUp();
    void                                    handleRemoveSelected();
    void                                    addToMenu(const PDF_Info_Historical_Record& g);
    void                                    update_ui(PDF_Info_Historical_Record g);
    void                                    removeFromOutward(const QString& path);
signals:
    void                                    emitTellRemovePdfPath(QString self_file_path);
    void                                    emitTellLoadPdf(QString self_file_path);

private:
    void                                        initMenu();
    QPoint                                      exePoint;
    __MEMEROY_NO_HOLD   QTableWidget*           operatingWidget;
    __MEMEROY_HOLD_BY_OBJ_TREE QMenu*           operatingWidgetMenu;
};

#endif // CCPDF_HISTORYTABLEWIDGETCONTROLLER_H
