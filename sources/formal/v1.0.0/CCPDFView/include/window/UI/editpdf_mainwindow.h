#ifndef EDITPDF_MAINWINDOW_H
#define EDITPDF_MAINWINDOW_H
#include <QMainWindow>

class QPushButton;
class KeyBoardEventHandler;
class EditReactor;
class HistoricalOperation_Reactor;
class SaveReactor;
class PDF_Window_SavingConfig;

template<class T>
class ActionHandler;

namespace Ui {
class EditPDF_MainWindow;
}

class EditPDF_MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum class FlagState
    {
        Creating,
        Editing,
        Moving
    }state = FlagState::Creating;
    const short                         TAB_MARKER_INDEX    = 0;
    const short                         TAB_TEXT_INDEX      = 1;
    explicit                            EditPDF_MainWindow(QWidget *parent = nullptr);
    ~EditPDF_MainWindow();
    void                                setCurrentEditingImage(QImage image, QString pdfPath);
    bool                                removeTheSelectedItems();
    bool                                resumeLastState();
    bool                                resumeLastResume();
    bool                                removeAllItems();
    QPixmap                             getEditedImage();
    bool                                setAsSave();
    bool                                quit();
    void                                closeEvent(QCloseEvent*);
    void                                keyPressEvent(QKeyEvent*);
    void                                keyReleaseEvent(QKeyEvent*);
signals:
    void                                finishEditCurPage();
private slots:
    void setDrawingRectTransparency(short value);

    void setDrawingTextTransparency(short value);

    void setDrawingRectColor(QColor c);

    void setDrawingTextColor(QColor c);

    void backToEditingMode();

    bool on_btn_addMarker_clicked();

    void on_horizontalSlider_transparency_valueChanged(int value);

    void on_btn_setColor_clicked();

    void on_horizontalSlider_currentWidth_valueChanged(int value);

    void on_horizontalSliderCurrentHeight_valueChanged(int value);

    bool on_btn_addText_clicked();

    void on_btn_setColor_text_clicked();

    void on_textEditPlace_textChanged();

    void on_horizontalSlider_transparency_text_valueChanged(int value);

    void on_btn_setColor_textfont_clicked();

    void on_btn_setColor_textbackground_clicked();

    void on_rermove_selected_clicked();

    void on_btn_resumeLastOperation_clicked();

    void on_btn_resumeLastResume_clicked();

    void on_Edited_toolBox_currentChanged(int index);

    void on_btn_refresh_clicked();

    void on_btn_save_clicked();

    void on_toolsTab_tabBarClicked(int index);

    void on_remove_all_clicked();

private:
    const short                         IS_SAVE_TOOLBOX_INDEX = 2;
    enum class DrawingFocusing{
        WIDTH,
        HIEGHT,
        COLOR,
        TRANSPARENCY,
        BACKGROUND_COLOR,
    };

    Ui::EditPDF_MainWindow*             ui;
    QImage                              image;
    QPixmap                             after_edited;
    QString                             pdfPath;
    KeyBoardEventHandler*               keyhandle = nullptr;
    ActionHandler<EditPDF_MainWindow>*  actionHandler = nullptr;
    QList<HistoricalOperation_Reactor*> histOperator;
    QList<EditReactor*>                 editFunctors;
    QList<SaveReactor*>                 saveFunctors;
    PDF_Window_SavingConfig*            savingManager;
    bool                                isEditedSave = false;
    // init
    void                                initCore();
    void                                initUi();
    void                                initKeyhandle();
    void                                initConnections();
    void                                initToolBars();
    void                                updateUiIcon(QPushButton* who, QColor what);
    void                                handleCurrntFocusItem(DrawingFocusing s, int val, QColor c);
    void                                handleCurrentFocusTextSize(QString val);
    void                                handleCurrentFocusTextFont(QFont f);
    void                                handleTransparency(short val);
};

#endif // EDITPDF_MAINWINDOW_H
