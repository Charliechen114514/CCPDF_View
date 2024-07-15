#ifndef CCPDF_STRINGPARSEUTIL_H
#define CCPDF_STRINGPARSEUTIL_H
#include <utility>
#include <QStringList>

struct CCPDF_StringParseUtil
{
    static std::pair<bool, int> parseToInt(const QString& number){
        bool ok = false; return {ok, number.toInt(&ok)};
    }
};


#endif // CCPDF_STRINGPARSEUTIL_H
