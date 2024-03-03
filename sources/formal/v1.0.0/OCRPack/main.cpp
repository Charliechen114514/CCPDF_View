#include <QCoreApplication>
#define PICPATH "D:\\test_imgs\\1.png"
#define PICPATH2 "D:\\test_imgs\\2.png"
#define PICPATH3 "D:\\test_imgs\\3.png"
#define PICPATH4 "D:\\test_imgs\\4.png"
#define EXEPATH "D:\\Tesseract\\tesseract.exe"
#define RES     "D:\\QT projects\\OCRPack\\res\\"
#define WORK    "D:\\test_imgs\\55.png"
#include "ocrpackage.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    OCRPackage p;
    QStringList pics;
    pics << PICPATH << PICPATH2 << PICPATH3 << PICPATH4 << PICPATH4 << PICPATH3 << PICPATH2 << PICPATH;
    pics << WORK;
    p.addMutltiPics(pics);
    p.configExecutableOCRPath(EXEPATH);
    p.configSavingDirPath(RES);
    if(p.checkMissionStartAble())
        p.startRecognize();
    else
        qDebug() << p.errorString();
    return a.exec();
}
