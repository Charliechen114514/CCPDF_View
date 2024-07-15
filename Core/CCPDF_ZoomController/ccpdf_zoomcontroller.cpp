#include "ccpdf_zoomcontroller.h"
#include "CCPDF_SinglePDF_Component/ccpdf_singlepdf_widget.h"
#include "CCPDF_PdfView/ccpdf_mypdfview.h"

CCPDF_ZoomController::CCPDF_ZoomController(const double InitZoomFactor)
    :current_zoom_percentage(InitZoomFactor)
{}

bool CCPDF_ZoomController::zoomIn()
{
    if(!checkVadility())
        return false;
    if(!checkParamVadility())
        return false;
    operating_widget->getView()->setZoomFactor(current_zoom_percentage * zoomInPer);
    current_zoom_percentage *= zoomInPer;
    return true;
}

bool CCPDF_ZoomController::zoomOut()
{
    if(!checkVadility())
        return false;
    if(!checkParamVadility())
        return false;
    operating_widget->getView()->setZoomFactor(current_zoom_percentage * zoomOutPer);
    current_zoom_percentage *= zoomOutPer;
    return true;
}

bool CCPDF_ZoomController::setZoomPercentage(const double per)
{
    if(!checkVadility())
        return false;
    if(!tryCheckParamVadility(per))
        return false;
    operating_widget->getView()->setZoomFactor(per);
    return true;
}

bool CCPDF_ZoomController::checkVadility()
{
    if(!operating_widget->getView())
    {
        e.e = ZoomError::Error::NO_BIND_PDF;
        return false;
    }
    return true;
}

bool CCPDF_ZoomController::tryCheckParamVadility(const double& d)
{
    return  ZOOM_CONFIG_CONST::ZOOM_MIN_MINOR_EDGE < d &&
            d < ZOOM_CONFIG_CONST::ZOOM_MAX_UPPER_EDGE;
}


bool CCPDF_ZoomController::checkParamVadility()
{
    if(current_zoom_percentage > ZOOM_CONFIG_CONST::ZOOM_MAX_UPPER_EDGE){
        current_zoom_percentage = ZOOM_CONFIG_CONST::ZOOM_MAX_UPPER_EDGE;
        e.e = ZoomError::Error::ZOOM_TO_MAX;
        return false;
    }

    if(current_zoom_percentage < ZOOM_CONFIG_CONST::ZOOM_MIN_MINOR_EDGE){
        current_zoom_percentage = ZOOM_CONFIG_CONST::ZOOM_MIN_MINOR_EDGE;
        e.e = ZoomError::Error::ZOOM_TO_MIN;
        return false;
    }

    return true;
}

double CCPDF_ZoomController::zoomFactor()
{
    if(!checkVadility())
        return false;
    return operating_widget->getView()->zoomFactor();
}


CCPDF_ZoomController::~CCPDF_ZoomController()
{
    qDebug() << "Erasing Zoom Controller";
}
