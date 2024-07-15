#ifndef CCPDF_LINKWIDGET_H
#define CCPDF_LINKWIDGET_H

#include <QWidget>
class QPdfLinkModel;
namespace Ui {
class CCPDF_LinkWidget;
}

class CCPDF_LinkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit    CCPDF_LinkWidget(QWidget *parent = nullptr);
    void        handleLink(const QModelIndex& index);
    void        setModel(QPdfLinkModel* model);
    ~CCPDF_LinkWidget();
signals:
    void        navigateTo(int page);

private:
    Ui::CCPDF_LinkWidget *ui;
};

#endif // CCPDF_LINKWIDGET_H
