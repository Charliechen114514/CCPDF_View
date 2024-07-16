#ifndef CCPDF_BOOKMARKMODEL_H
#define CCPDF_BOOKMARKMODEL_H

#include <QPdfBookmarkModel>

class CCPDF_BookMarkModel : public QPdfBookmarkModel
{
public:
    explicit CCPDF_BookMarkModel(QObject *parent = nullptr);
    ~CCPDF_BookMarkModel() = default;

private:
    struct BookModelConfig{
        static constexpr short DEFUALT_COL = 2;
        static constexpr short TITLE_INDEX = 0;
        static constexpr short PAGE_INDEX = 1;
        static constexpr const char* TITLE = "标题";
        static constexpr const char* PAGE = "页码";

    };
    int                 columnCount(const QModelIndex &parent[[maybe_unused]]) const{return BookModelConfig::DEFUALT_COL;}
    QVariant            headerData(int section, Qt::Orientation orientation,int role) const;
    QVariant            data(const QModelIndex &index, int role) const;
    QStringList         myHeaders{BookModelConfig::TITLE, BookModelConfig::PAGE};
};

#endif // CCPDF_BOOKMARKMODEL_H
