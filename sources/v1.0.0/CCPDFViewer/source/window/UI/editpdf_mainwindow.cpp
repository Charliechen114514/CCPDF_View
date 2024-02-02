#include "editpdf_mainwindow.h"
#include "ui_editpdf_mainwindow.h"
const char* EDIT_WINDOW = "编辑";
EditPDF_MainWindow::EditPDF_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditPDF_MainWindow)
{
    ui->setupUi(this);
    QPalette pa;
    pa.setColor(QPalette::ColorRole::Window, QColor(255,255,255));
    ui->imageFrame->setPalette(pa);
    setWindowTitle(EDIT_WINDOW);
}

void EditPDF_MainWindow::setCurrentEditingImage(QImage image, QString pdfPath)
{
    this->image = image;
    this->pdfPath = pdfPath;
    disPlayImage();
}

void EditPDF_MainWindow::disPlayImage()
{
    if(!this->image.isNull())
        ui->imageFrame->setPixmap(QPixmap::fromImage(this->image));
}


EditPDF_MainWindow::~EditPDF_MainWindow()
{
    delete ui;
}
