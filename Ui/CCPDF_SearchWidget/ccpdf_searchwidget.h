#ifndef CCPDF_SEARCHWIDGET_H
#define CCPDF_SEARCHWIDGET_H
#include <QWidget>
#include <QModelIndex>
class QPdfSearchModel;
namespace Ui {
class CCPDF_SearchWidget;
}

class CCPDF_SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit    CCPDF_SearchWidget(QWidget *parent = nullptr);
    void        setModel(QPdfSearchModel* view);
    void        handleSearch(const QModelIndex& cur, const QModelIndex& prev);
    void        handleTellString();
    ~CCPDF_SearchWidget();
signals:
    void        tellPageNavigate(const int page, QPointF where, const QModelIndex& index);
    void        tellString(const QString res);
private:
    Ui::CCPDF_SearchWidget *ui;
};

#endif // CCPDF_SEARCHWIDGET_H
