#include "paintingpackage.h"
#include <QGraphicsScene>
#include <QTextCursor>
#include <QFontMetricsF>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

DrawingRect::DrawingRect(QRect f, QGraphicsItem* item):QGraphicsRectItem(item)
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    actualRect = f;
    setRect(f);
    flag = OperatingFlag::Moving;
}

DrawingRect& DrawingRect::setTheTargetRect(QRect f)
{
    actualRect = f;
    setRect(f);
    flag = OperatingFlag::Moving;
    return *this;
}


DrawingRect& DrawingRect::setColor(QColor c)
{
    QBrush t;
    t.setStyle(Qt::BrushStyle::SolidPattern);
    t.setColor(c);
    rectColor = c;
    this->setBrush(t);
    return *this;
}

DrawingRect& DrawingRect::setPenColor(QColor c)
{
    QPen t;
    t.setColor(c);
    this->setPen(t);
    return *this;
}

DrawingRect& DrawingRect::setSize(int w, int h)
{
    this->actualRect.setHeight(h);
    this->actualRect.setWidth(w);
    this->setRect(this->boundingRect());
    return *this;
}


DrawingRect::DrawingRect(const DrawingRect& other):QGraphicsRectItem(other.parentItem())
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

void DrawingRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    movingConfig.setMovable(true);
    movingConfig.setStartPos(event->pos());
    return QGraphicsItem::mousePressEvent(event);
}

void DrawingRect::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(movingConfig.getMovable())
    {
        this->moveBy(movingConfig.getMovedPair(event->pos()).x(),
                     movingConfig.getMovedPair(event->pos()).y());
        return QGraphicsItem::mouseMoveEvent(event);
    }
}

void DrawingRect::mouseReleaseEvent(QGraphicsSceneMouseEvent* event[[maybe_unused]])
{
    // recover the normal state
    movingConfig.setMovable(false);
    return QGraphicsItem::mouseReleaseEvent(event);
}


QRectF DrawingRect::boundingRect()const
{
    return actualRect;
}

void DrawingRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option[[maybe_unused]], QWidget*)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(this->brush());
    painter->drawRect(actualRect);
}


DrawingText::DrawingText(const QRect rt, QGraphicsItem* item):DrawingRect(rt, item)
{
    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    this->actualRect = rt;
    this->rectColor = DEFAULT_BK_COLOR;
}


void DrawingText::setText(QString text)
{
    currentText = text;
}

void DrawingText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget* widget)
{
    // 先画DrawingRect
    painter->save();
    DrawingRect::paint(painter, option, widget);
    painter->restore();
    QPen thispen(fontColor);
    painter->setPen(thispen);
    painter->setFont(currentFont);
    painter->setRenderHint(QPainter::Antialiasing, true);//防止出现锯齿现象（反锯齿绘制）
    painter->drawText(this->boundingRect(), currentText);
}

#include <QColorDialog>
QColor ColorManager::getColorFromUserChoice(){
    return QColorDialog::getColor();
}

QIcon ColorManager::getPureIcon(QColor c){
    QPixmap pix(32, 32);
    pix.fill(c);
    return QIcon(pix);
}


#include <QFontDialog>
QFont TextFontManager::getFontFromUserChoice(){
    bool isOk;
    return QFontDialog::getFont(&isOk);
}




















