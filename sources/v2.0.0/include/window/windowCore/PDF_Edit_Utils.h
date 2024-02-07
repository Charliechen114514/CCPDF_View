#ifndef PDF_EDIT_UTILS_H
#define PDF_EDIT_UTILS_H
#include <QPoint>
#include <QRect>
class GenPointPosInWidget
{
public:
    static QPoint getPointPosInWidget(QPoint mousePos, QPoint WidgetBegin){
        return mousePos - WidgetBegin;
    }
};

class TextCounter
{
public:
    static int getSlashCount(QString txt)
    {
        int size = 1;
        for(auto each : txt)
        {
            if(each == '\n')
                size++;
        }
        return size;
    }
};



class MovingConfig
{
public:
    MovingConfig() = default;
    MovingConfig(const MovingConfig&) = delete;
    const MovingConfig& operator=(const MovingConfig&) = delete;
    void            setStartPos(QPointF p){m_start_point = p;}
    void            setMovable(bool st){isSupposedMove = st;};
    bool&           getMovable(){return isSupposedMove;}
    QPointF&        getStartPos(){return m_start_point;}
    QPointF         getMovedPair(QPointF curPos){return curPos - m_start_point;}
private:
    QPointF         m_start_point;
    bool            isSupposedMove = false;
};









#endif // PDF_EDIT_UTILS_H
