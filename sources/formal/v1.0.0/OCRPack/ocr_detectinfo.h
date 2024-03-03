#ifndef OCR_DETECTINFO_H
#define OCR_DETECTINFO_H
#include <QFile>


class OCR_DetectInfo
{
public:
    OCR_DetectInfo(int index, QString filePath):filePath(filePath),index(index){}
    OCR_DetectInfo() = delete;
    OCR_DetectInfo(const OCR_DetectInfo&) = delete;
    const OCR_DetectInfo& operator=(const OCR_DetectInfo&) = delete;

    void getInfos(){
        QFile f(filePath);
        f.open(QIODevice::ReadOnly);
        if(f.isOpen())
        {
            text = f.readAll();
        }
    }

    QString getRes(){return text;}

    int getIndex(){return index;}

    QString operator()(){
        getInfos();
        return text;
    }
private:
    QString filePath;
    int     index = 0;
    QString text;
};

#endif // OCR_DETECTINFO_H
