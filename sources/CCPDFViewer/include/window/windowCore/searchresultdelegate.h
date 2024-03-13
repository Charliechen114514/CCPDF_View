#ifndef SEARCHRESULTDELEGATE_H
#define SEARCHRESULTDELEGATE_H

#include <QStyledItemDelegate>

class SearchingResultDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    SearchingResultDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // SEARCHRESULTDELEGATE_H
