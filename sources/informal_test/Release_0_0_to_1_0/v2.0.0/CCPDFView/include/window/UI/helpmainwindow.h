#ifndef HELPMAINWINDOW_H
#define HELPMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class HelpMainWindow;
}

class HelpMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HelpMainWindow(QWidget *parent = nullptr);
    ~HelpMainWindow();

private:
    Ui::HelpMainWindow *ui;
};

#endif // HELPMAINWINDOW_H
