#ifndef CCPDF_ZOOMCONTROLLER_H
#define CCPDF_ZOOMCONTROLLER_H
#include "CCPDF_Global.h"
class CCPDF_SinglePDF_Widget;

class CCPDF_ZoomController
{
public:
    struct ZOOM_CONFIG_CONST{
        static constexpr    double  ZOOM_IN_PERCENTAGE_EACH_DEFAULT     = 1.1;
        static constexpr    double  ZOOM_OUT_PERCENTAGE_EACH_DEFAULT    = 0.9;
        static constexpr    double  ZOOM_DEF_PERCENTAGE                 = INIT_PARAMS::ZOOM_INIT;
        static constexpr    double  ZOOM_MAX_UPPER_EDGE                 = 10;
        static constexpr    double  ZOOM_MIN_MINOR_EDGE                 = 0.4;
    };

    CCPDF_ZoomController() = delete;
    CCPDF_ZoomController(const double InitZoomFactor = ZOOM_CONFIG_CONST::ZOOM_DEF_PERCENTAGE);
    CCPDF_ZoomController(const CCPDF_ZoomController&) = delete;
    const CCPDF_ZoomController& operator=(const CCPDF_ZoomController&) = delete;
    ~CCPDF_ZoomController();



    struct ZoomError{
        enum class Error
        {
            NO_ERROR,
            NO_BIND_PDF,
            ZOOM_TO_MAX,
            ZOOM_TO_MIN
        } e {ZoomError::Error::NO_ERROR};
        QString errorString(){
            switch(e)
            {
            case Error::NO_BIND_PDF:
                return "No PDF_Register!";
            case Error::ZOOM_TO_MAX:
                return "Zoom to Max";
            case Error::ZOOM_TO_MIN:
                return "Zoom to Min";
            case Error::NO_ERROR:
                return "No  error";
                break;
            }
            return "Unknown Error";
        }
    };

    void                setOperatingPDF(CCPDF_SinglePDF_Widget* view){operating_widget = view;}
    CCPDF_SinglePDF_Widget* widget() const {return operating_widget;}
    void                setZoomInPercentage(const double zoomInPer){this->zoomInPer = zoomInPer;}
    void                setZoomOutPercentage(const double zoomOutPer){this->zoomOutPer = zoomOutPer;}
    bool                zoomIn();
    bool                zoomOut();
    bool                setZoomPercentage(const double per);
    ZoomError::Error    getError() {return e.e;}
    double              zoomFactor();
    void                clearError(){e.e = ZoomError::Error::NO_ERROR;};
private:
    __MEMEROY_NO_HOLD   CCPDF_SinglePDF_Widget*    operating_widget{nullptr};
    bool                checkVadility();
    bool                checkParamVadility();
    bool                tryCheckParamVadility(const double& d);
    double              zoomInPer {ZOOM_CONFIG_CONST::ZOOM_IN_PERCENTAGE_EACH_DEFAULT};
    double              zoomOutPer {ZOOM_CONFIG_CONST::ZOOM_OUT_PERCENTAGE_EACH_DEFAULT};
    double              current_zoom_percentage;
    ZoomError           e;
};

#endif // CCPDF_ZOOMCONTROLLER_H
