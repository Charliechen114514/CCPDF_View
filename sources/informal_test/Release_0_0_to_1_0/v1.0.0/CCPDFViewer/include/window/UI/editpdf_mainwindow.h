#ifndef EDITPDF_MAINWINDOW_H
#define EDITPDF_MAINWINDOW_H
#include <QImage>
#include <QMainWindow>



namespace Ui {
class EditPDF_MainWindow;
}

class EditPDF_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit    EditPDF_MainWindow(QWidget *parent = nullptr);
    void        setCurrentEditingImage(QImage image, QString pdfPath);
    void        disPlayImage();
    ~EditPDF_MainWindow();

private:
    Ui::EditPDF_MainWindow *            ui;
    QImage                              image;
    QString                             pdfPath;
};

#endif // EDITPDF_MAINWINDOW_H
