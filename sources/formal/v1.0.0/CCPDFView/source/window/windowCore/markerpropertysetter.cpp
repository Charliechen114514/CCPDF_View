#include "markerpropertysetter.h"
#include "paintingpackage.h"
#include <QFontMetricsF>

MarkerPropertySetter::MarkerPropertySetter()
{
    currentColor = DEFAULT_COLOR;
    transparency = DEFAULT_TRANSPARENCY;
}

QColor MarkerPropertySetter::getMarkerColor()
{
    return QColor(currentColor.red(), currentColor.green(), currentColor.blue(), transparency);
}

void MarkerPropertySetter::setProperty(DrawingRect* d)
{
    d->setColor(getMarkerColor());
    d->update();
}

TextItemPropertySetter::TextItemPropertySetter()
{
    currentTextColor = DEFAULT_FONT_COLOR;
    transparency = DEFAULT_BACKGROUND_TRANSPARENCY;
    backGroundColor = DEFAULT_BACKGROUND_COLOR;
}

QSize TextItemPropertySetter::getStringSize(QString textCurrent, QFont f)
{
    return QFontMetricsF(f).size(Qt::TextExpandTabs, textCurrent).toSize();
}

int TextItemPropertySetter::getTextLength()
{
    return QFontMetricsF(textFont).size(Qt::TextSingleLine, textCurrent).width();
}

int TextItemPropertySetter::getTextHeight()
{
    return QFontMetricsF(textFont).size(Qt::TextSingleLine, textCurrent).height();
}

QColor TextItemPropertySetter::getBackGroundColor()
{
    return QColor(backGroundColor.red(),
                  backGroundColor.green(),
                  backGroundColor.blue(),
                  transparency);
}


void TextItemPropertySetter::setProperty(DrawingText* t){
    t->setFontColor(currentTextColor);
    t->setText(textCurrent);
    t->setColor(getBackGroundColor());
    t->setFont(textFont);
    t->setBackColor(backGroundColor);
    t->setRect(t->boundingRect().x(), t->boundingRect().y(), getTextLength(),getTextHeight());
}
