#ifndef CCPDF_HELPWINDOW_H
#define CCPDF_HELPWINDOW_H
#include <QMap>
#include <QMainWindow>

namespace Ui {
class CCPDF_HelpWindow;
}

class CCPDF_HelpWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit    CCPDF_HelpWindow(QWidget *parent = nullptr);
    void        configMap();
    void        registerTabs();
    ~CCPDF_HelpWindow();

private:
    Ui::CCPDF_HelpWindow *ui;
    using TabName = QString;
    using FilePath = QString;
    QMap<TabName, FilePath> mappings;
};

#endif // CCPDF_HELPWINDOW_H
