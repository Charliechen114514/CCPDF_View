#ifndef CCPDF_BOOKLIBRARYWIDGET_H
#define CCPDF_BOOKLIBRARYWIDGET_H
#include <QWidget>
#include "CCPDF_Global.h"
class CCPDF_BookLibraryManager;

namespace Ui {
class CCPDF_BookLibraryWidget;
}

class CCPDF_BookLibraryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CCPDF_BookLibraryWidget(QWidget *parent = nullptr);
    ~CCPDF_BookLibraryWidget();
    void        setRootPath(const QString& Path);
    void        searchInRoot(const QString& fileName);
signals:
    void        tellLoadWhat(QString filePath);
    void        tellShellRecord(QString dirPath);
private slots:
    __BIND_Ui_No_Inline     void on_btn_set_bookLibPath_clicked();
    __BIND_Ui_No_Inline     void on_btn_book_lib_searching_search_clicked();
    __BIND_Ui_Widgets       void on_book_lib_searching_lineEdit_textChanged(const QString &arg1){searchInRoot(arg1);}

    void on_booklibrary_treeView_clicked(const QModelIndex &index);

private:
    Ui::CCPDF_BookLibraryWidget*                ui;
    __MEMEROY_HOLD_BY_SMT_PTR
    std::unique_ptr<CCPDF_BookLibraryManager>   manager;
};

#endif // CCPDF_BOOKLIBRARYWIDGET_H
