#ifndef MARKERPROPERTYSETTER_H
#define MARKERPROPERTYSETTER_H
#include "qfont.h"
#include <QColor>

class DrawingRect;
class DrawingText;
class MarkerPropertySetter
{
public:
    const QColor DEFAULT_COLOR = QColor(255, 0, 0, 100);
    const short DEFAULT_TRANSPARENCY = 100;
    MarkerPropertySetter();
    const MarkerPropertySetter& operator=(const MarkerPropertySetter&) = delete;
    MarkerPropertySetter(const MarkerPropertySetter&) = delete;
    void        setColor(QColor c){currentColor = c;}
    QColor      getCurrentColor(){return currentColor;}
    void        setTransParency(short trans){transparency = trans;}
    short       getTransParency(){return transparency;}
    QColor      getMarkerColor();
    void        setProperty(DrawingRect* item);
private:
    QColor      currentColor;
    short       transparency;
};

class TextItemPropertySetter
{
public:
    const QColor    DEFAULT_FONT_COLOR = QColor(255, 0, 0, 100);
    const short     DEFAULT_BACKGROUND_TRANSPARENCY = 100;
    const QColor    DEFAULT_BACKGROUND_COLOR  = QColor(255, 255, 255, 255);

    static QSize    getStringSize(QString text, QFont f);

    TextItemPropertySetter();
    const TextItemPropertySetter& operator=(const TextItemPropertySetter&) = delete;
    TextItemPropertySetter(const TextItemPropertySetter&) = delete;
    void            setCurrentColor(QColor c){currentTextColor = c;}
    void            setFont(QFont f){textFont = f;}
    QFont           getFont(){return textFont;}
    void            setText(QString text){textCurrent = text;}
    QString         getText(){return textCurrent;}
    int             getTextLength();
    int             getTextHeight();
    QColor          getCurrentColor(){return currentTextColor;}
    void            setProperty(DrawingText* t);
    QColor          getBackGroundColor();
    void            setBackGroundTransparency(short value){transparency = value;}
    void            setBackGroundColor(QColor c){backGroundColor = c;}
private:
    QString         textCurrent;
    QFont           textFont;
    QColor          currentTextColor;
    QColor          backGroundColor;
    short           transparency;
};


#endif // MARKERPROPERTYSETTER_H
