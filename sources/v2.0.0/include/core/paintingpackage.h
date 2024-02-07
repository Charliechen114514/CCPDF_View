#ifndef PAINTINGPACKAGE_H
#define PAINTINGPACKAGE_H
#include <QFont>
#include <QPen>
#include <QGraphicsItem>
#include "PDF_Edit_Utils.h"

class DrawingRect : public QGraphicsRectItem
{
public:
    enum class OperatingFlag
    {
        Moving,
        Creating,
    };

    DrawingRect() = delete; // disable the triditional
    DrawingRect(QRect f,  QGraphicsItem* parent = nullptr);
    DrawingRect(const DrawingRect&);
    void                setFlag(OperatingFlag f){flag = f;}
    OperatingFlag       getFlag(){return flag;}
    DrawingRect&        setTheTargetRect(QRect f);
    DrawingRect&        setColor(QColor c);
    DrawingRect&        setPenColor(QColor c);
    DrawingRect&        setSize(int w, int h);
    QPointF             getTopLeft(){return actualRect.topLeft();}
    QColor&             getColor(){return rectColor;}
    const DrawingRect&  operator=(const DrawingRect&) = delete;

public slots:
    virtual void        mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void        mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void        mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    virtual void        paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
    virtual QRectF      boundingRect()const;
protected:
    OperatingFlag       flag;// 当前的状态如何
    MovingConfig        movingConfig;
    QRect               actualRect;
    QColor              rectColor;
};


class DrawingText : public DrawingRect
{
public:
    enum class OperatingFlag
    {
        Moving,
        Creating,
    };
    const QColor        DEFAULT_BK_COLOR = QColor(255, 255, 255, 0);
    DrawingText(const QRect rt, QGraphicsItem* item = nullptr);
    void                setFlag(OperatingFlag f){flag = f;}
    OperatingFlag       getFlag(){return flag;}
    void                setText(QString text);
    QString             getText(){return this->currentText;}
    void                setFontColor(QColor c){fontColor = c;}
    QColor              getFontColor(){return fontColor;}
    void                setBackColor(QColor c){rectColor = c;}
    QColor              getBackColor(){return rectColor;}
    void                setFont(QFont f){currentFont = f;}
    QFont               getFont(){return currentFont;}
    QSize               getTextSize();

public slots:
    virtual void        paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

private:
    OperatingFlag       flag;
    MovingConfig        movingConfig;
    QString             currentText;
    QColor              fontColor;
    QFont               currentFont;
};



class ColorManager
{
public:
    static QColor   getColorFromUserChoice();
    static QIcon    getPureIcon(QColor c);
};

class TextFontManager
{
public:
    static QFont    getFontFromUserChoice();
};


#endif // PAINTINGPACKAGE_H
