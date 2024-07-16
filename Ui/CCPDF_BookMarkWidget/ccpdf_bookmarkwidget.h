#ifndef CCPDF_BOOKMARKWIDGET_H
#define CCPDF_BOOKMARKWIDGET_H
#include "CCPDF_Global.h"
#include "CCPDF_BookMarkManager/BookMarkModel/ccpdf_bookmarkmodel.h"
#include <QWidget>
class CCPDF_BookMarkModel;
class CCPDF_BookMarkManager;

namespace Ui {
class CCPDF_BookMarkWidget;
}

class CCPDF_BookMarkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit    CCPDF_BookMarkWidget(QWidget *parent = nullptr);
    void        setModel(CCPDF_BookMarkModel* m);
    ~CCPDF_BookMarkWidget();
signals:
    void                        navigateTo(const int pageIndex, const qreal zoomLevel);
private slots:
    __BIND_Ui_No_Inline void    on_bookmodel_treeView_activated(const QModelIndex &index);

private:
    Ui::CCPDF_BookMarkWidget *ui;
    __MEMEROY_NO_HOLD CCPDF_BookMarkManager* manager;
};

#endif // CCPDF_BOOKMARKWIDGET_H
