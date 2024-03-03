#ifndef PDF_MESSAGEBOX_H
#define PDF_MESSAGEBOX_H

#include <QMessageBox>

#define LOAD_CRITI_MSGBX(Wid, ERR) QMessageBox::critical(Wid, "加载错误", ERR)

#endif // PDF_MESSAGEBOX_H
