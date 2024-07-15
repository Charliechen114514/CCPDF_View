#ifndef CCPDF_BOOKLIRABRY_FILESYSTEMMODEL_H
#define CCPDF_BOOKLIRABRY_FILESYSTEMMODEL_H
#include <QFileSystemModel>

class CCPDF_BookLirabry_FileSystemModel : public QFileSystemModel
{
public:
    explicit    CCPDF_BookLirabry_FileSystemModel(QObject *parent = nullptr);
    ~CCPDF_BookLirabry_FileSystemModel() = default;
private:
    struct CONFIG_CONSTS{
        static constexpr short DEFAULT_COLUMN_SHOW = 1;
        static constexpr const char* PDF_ICON_PATH = ":/Ui/icons/pdf.ico";
    };

    QPixmap             pdf_icon {CONFIG_CONSTS::PDF_ICON_PATH};
    int                 columnCount(const QModelIndex &parent[[maybe_unused]]) const{return CONFIG_CONSTS::DEFAULT_COLUMN_SHOW;}
    QVariant            data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // CCPDF_BOOKLIRABRY_FILESYSTEMMODEL_H
