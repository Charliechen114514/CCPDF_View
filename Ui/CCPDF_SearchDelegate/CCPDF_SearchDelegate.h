#ifndef SEARCHRESULTDELEGATE_H
#define SEARCHRESULTDELEGATE_H

#include <QStyledItemDelegate>

class CCPDF_SearchDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CCPDF_SearchDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // SEARCHRESULTDELEGATE_H
