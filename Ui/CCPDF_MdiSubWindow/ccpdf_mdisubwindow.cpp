#include "ccpdf_mdisubwindow.h"
#include "CCPDF_SinglePDF_Component/ccpdf_singlepdf_widget.h"

CCPDF_MdiSubWindow::CCPDF_MdiSubWindow(QWidget* parent)
    :QMdiSubWindow(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
}

void CCPDF_MdiSubWindow::setWidget(QWidget* w)
{
    this->w = dynamic_cast<CCPDF_SinglePDF_Widget*>(w);
    return QMdiSubWindow::setWidget(w);
}


void CCPDF_MdiSubWindow::closeEvent(QCloseEvent* env)
{
    emit self_close(w->pdfPath());
    return QMdiSubWindow::closeEvent(env);
}

