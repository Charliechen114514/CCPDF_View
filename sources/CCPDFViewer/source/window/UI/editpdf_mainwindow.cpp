#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QPdfWriter>
#include <QCloseEvent>
#include <QMessageBox>
#include "PDF_Utils.h"
#include "eventhandler.h"
#include "pdf_Reactor.h"
#include "ui_editpdf_mainwindow.h"
#include "editpdf_mainwindow.h"
#include "paintingpackage.h"
#include "markerpropertysetter.h"

static const char* EDIT_WINDOW = "编辑";


EditPDF_MainWindow::EditPDF_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditPDF_MainWindow)
{
    ui->setupUi(this);
    initCore();
    initUi();
    initKeyhandle();
    initConnections();
    initToolBars();
    setWindowTitle(EDIT_WINDOW);
}

void EditPDF_MainWindow::setCurrentEditingImage(QImage image, QString pdfPath)
{
    this->image = image;
    this->pdfPath = pdfPath;
    ui->imageFrame->bindBackGroundImage(image);
}

void EditPDF_MainWindow::initCore()
{
    setAcceptDrops(true);
    setMouseTracking(true);
    connect(ui->imageFrame, &PDF_EditGraphicView::EmitTheFinishCreation,
            this, &EditPDF_MainWindow::backToEditingMode);
    this->savingManager = new PDF_Window_SavingConfig;
}

void EditPDF_MainWindow::initUi()
{
    ui->btn_setColor->setIcon(
        ColorManager::getPureIcon(ui->imageFrame->interfaceOfMarkerManager()->DEFAULT_COLOR));
    ui->btn_setColor_text->setIcon(
        ColorManager::getPureIcon(ui->imageFrame->interfaceOfTextManager()->DEFAULT_FONT_COLOR));
    ui->btn_setColor_text->setIcon(
        ColorManager::getPureIcon(ui->imageFrame->interfaceOfTextManager()->DEFAULT_BACKGROUND_COLOR));
}

void EditPDF_MainWindow::initKeyhandle()
{
    keyhandle = new KeyBoardEventHandler;
    histOperator.push_back((new HistoricalOperation_Reactor())
    ->setFunctor(std::bind(&EditPDF_MainWindow::resumeLastState, this))
    ->setRequired_modifiers(Qt::KeyboardModifier::ControlModifier)); // Ctrl Z [0]

    histOperator.push_back((new HistoricalOperation_Reactor())
    ->setFunctor(std::bind(&EditPDF_MainWindow::resumeLastResume, this))
    ->setRequired_modifiers(Qt::KeyboardModifier::ControlModifier)); // Ctrl Y [1]

    keyhandle->registerEventHandle(Qt::Key::Key_Z, histOperator[0]);
    keyhandle->registerEventHandle(Qt::Key::Key_Y, histOperator[1]);

    editFunctors.push_back(
        (new EditReactor())
        ->setRequired_modifiers(Qt::KeyboardModifier::ControlModifier)
        ->setFunctor(std::bind(&EditPDF_MainWindow::on_btn_addMarker_clicked, this))
    ); // [0]

    editFunctors.push_back(
        (new EditReactor())
        ->setRequired_modifiers(Qt::KeyboardModifier::ControlModifier)
        ->setFunctor(std::bind(&EditPDF_MainWindow::on_btn_addText_clicked, this))
    ); // [1]

    keyhandle->registerEventHandle(Qt::Key::Key_M, editFunctors[0]);
    keyhandle->registerEventHandle(Qt::Key::Key_T, editFunctors[1]);

    saveFunctors.push_back(
        (new SaveReactor())
            ->setRequired_modifiers(Qt::KeyboardModifier::ControlModifier)
            ->setFunctor(std::bind(&EditPDF_MainWindow::setAsSave,this))
    );

    keyhandle->registerEventHandle(Qt::Key::Key_S, saveFunctors[0]);
}

void EditPDF_MainWindow::initConnections()
{
    actionHandler = new ActionHandler<EditPDF_MainWindow>;
    actionHandler->insertConnections(ui->action_createMarker, &EditPDF_MainWindow::on_btn_addMarker_clicked);
    actionHandler->insertConnections(ui->action_createText, &EditPDF_MainWindow::on_btn_addText_clicked);
    actionHandler->insertConnections(ui->action_resume, &EditPDF_MainWindow::resumeLastState);
    actionHandler->insertConnections(ui->action_resumeTheResume, &EditPDF_MainWindow::resumeLastResume);
    actionHandler->insertConnections(ui->action_save, &EditPDF_MainWindow::setAsSave);
    actionHandler->insertConnections(ui->action_quit, &EditPDF_MainWindow::quit);
    actionHandler->insertConnections(ui->action_deleteThis, &EditPDF_MainWindow::removeTheSelectedItems);
    actionHandler->insertConnections(ui->action_deleteAll, &EditPDF_MainWindow::removeAllItems);
    actionHandler->connectAll(this);
}

void EditPDF_MainWindow::initToolBars()
{
    // 添加
    QPushButton* add_marker = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(add_marker);
    add_marker->setToolTip("添加荧光笔");
    add_marker->setIcon(QIcon(":/toolbar_icon/pic/marker.png"));
    connect(add_marker, &QPushButton::clicked, this, &EditPDF_MainWindow::on_btn_addMarker_clicked);

    QPushButton* add_text = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(add_text);
    add_text->setToolTip("添加文本框");
    add_text->setIcon(QIcon(":/toolbar_icon/pic/Text.png"));
    connect(add_text, &QPushButton::clicked, this, &EditPDF_MainWindow::on_btn_addText_clicked);
    ui->toolBar->addSeparator();

    // 撤销
    QPushButton* resumeBtn = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(resumeBtn);
    resumeBtn->setToolTip("撤回");
    resumeBtn->setIcon(QIcon(":/toolbar_icon/pic/resume.png"));
    connect(resumeBtn, &QPushButton::clicked, this, &EditPDF_MainWindow::resumeLastState);

    QPushButton* resumeResumeBtn = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(resumeResumeBtn);
    resumeResumeBtn->setToolTip("恢复");
    resumeResumeBtn->setIcon(QIcon(":/toolbar_icon/pic/resumeTheresume.png"));
    connect(resumeResumeBtn, &QPushButton::clicked, this, &EditPDF_MainWindow::resumeLastResume);
    ui->toolBar->addSeparator();

    // save
    QPushButton* saveBtn = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(saveBtn);
    saveBtn->setToolTip("保存");
    saveBtn->setIcon(QIcon(":/toolbar_icon/pic/savePDF.png"));
    connect(saveBtn, &QPushButton::clicked, this, &EditPDF_MainWindow::setAsSave);
    ui->toolBar->addSeparator();

    // del
    QPushButton* delThis = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(delThis);
    delThis->setToolTip("删除选中");
    delThis->setIcon(QIcon(":/toolbar_icon/pic/cancelSelect.png"));
    connect(delThis, &QPushButton::clicked, this, &EditPDF_MainWindow::removeTheSelectedItems);

    QPushButton* delAll = new QPushButton(ui->toolBar);
    ui->toolBar->addWidget(delAll);
    delAll->setToolTip("删除所有");
    delAll->setIcon(QIcon(":/toolbar_icon/pic/cancelSelect.png"));
    connect(delAll, &QPushButton::clicked, this, &EditPDF_MainWindow::removeAllItems);
    ui->toolBar->addSeparator();
}


// 处理关闭事件
void EditPDF_MainWindow::closeEvent(QCloseEvent* env)
{
    // Ctrl + S saves
    if(isEditedSave)
    {
        emit finishEditCurPage();
        env->accept();
        return;
    }
    // none ctrl + S saved
    if(savingManager->checkIfNeedQueryingSave())
    {
        QMessageBox::StandardButton res = savingManager->alterQuestions(this, "尚未保存编辑，你确定退出");
        if(QMessageBox::Cancel == res)
        {
            env->ignore();
            return;
        }
        else if(QMessageBox::No == res)
            env->accept();
        else
            emit finishEditCurPage();
    }
    env->accept();
}

void EditPDF_MainWindow::keyPressEvent(QKeyEvent* env)
{
    keyhandle->setCurrentModifiers(env->modifiers());
    keyhandle->doProcess(env->key());
}

void EditPDF_MainWindow::keyReleaseEvent(QKeyEvent*)
{
    keyhandle->clearModifiers();
}


void EditPDF_MainWindow::updateUiIcon(QPushButton* who, QColor what)
{
    if(!who || !what.isValid())
        return;
    who->setIcon(ColorManager::getPureIcon(what));
}


void EditPDF_MainWindow::setDrawingRectTransparency(short value)
{
    ui->imageFrame->interfaceOfMarkerManager()->setTransParency(value);
    handleCurrntFocusItem(DrawingFocusing::TRANSPARENCY, value, QColor());
}

void EditPDF_MainWindow::setDrawingTextTransparency(short value)
{
    ui->imageFrame->interfaceOfTextManager()->setBackGroundTransparency(value);
    handleCurrntFocusItem(DrawingFocusing::TRANSPARENCY, value, QColor());
}

bool EditPDF_MainWindow::removeTheSelectedItems()
{
    ui->imageFrame->clearSelectedItems();
    return true;
}

bool EditPDF_MainWindow::resumeLastState()
{
    ui->imageFrame->resumeLastState();
    return true;
}

bool EditPDF_MainWindow::resumeLastResume()
{
    ui->imageFrame->resumeLastResume();
    return true;
}

bool EditPDF_MainWindow::removeAllItems()
{
    if(!PDF_Window_SavingConfig::generalAskForLeave(this,   "操作将会不可逆！"
                                                            "所有的操作和垃圾桶内的编辑都会清空！"
                                                            "你确定吗?"))
        return false;
    ui->imageFrame->clearAllItems();
    ui->imageFrame->bindBackGroundImage(image);
    setAsSave();
    isEditedSave = false;
    return true;
}

// 回归编辑模式：
void EditPDF_MainWindow::backToEditingMode()
{
    state = FlagState::Editing;
    ui->btn_setColor->setText("编辑颜色");
    ui->btn_setColor_text->setText("编辑字体颜色");
    ui->btn_setColor_textbackground->setText("编辑背景颜色");
    ui->btn_setColor_textfont->setText("编辑字体类型及其大小");
}

// 设置Rect颜色
void EditPDF_MainWindow::setDrawingRectColor(QColor c)
{
    if(state == FlagState::Creating)
    {
        ui->btn_setColor->setIcon(ColorManager::getPureIcon(c));
        ui->imageFrame->interfaceOfMarkerManager()->setColor(c);
    }
    else
    {
        handleCurrntFocusItem(DrawingFocusing::COLOR, 0, c);
    }
}

// 设置文本颜色
void EditPDF_MainWindow::setDrawingTextColor(QColor c)
{
    if(state == FlagState::Creating)
    {
        ui->btn_setColor_text->setIcon(ColorManager::getPureIcon(c));
        ui->imageFrame->interfaceOfTextManager()->setCurrentColor(c);
    }
    else
    {
        handleCurrntFocusItem(DrawingFocusing::COLOR, 0, c);
    }
}

// 处理文本框字体
void EditPDF_MainWindow::handleCurrentFocusTextFont(QFont f)
{
    QList<QGraphicsItem*> it = ui->imageFrame->sceneInterFace()->selectedItems();
    for(auto& e : it)
    {
        DrawingText* curIsText = dynamic_cast<DrawingText*>(e);
        if(curIsText)
        {
            TextItemPropertySetter* setter = ui->imageFrame->interfaceOfTextManager();
            setter->setFont(f);
            setter->setProperty(curIsText);
            curIsText->update();
        }
    }
}

// 处理文本框大小
void EditPDF_MainWindow::handleCurrentFocusTextSize(QString val)
{
    QList<QGraphicsItem*> it = ui->imageFrame->sceneInterFace()->selectedItems();
    for(auto& e : it)
    {
        DrawingText* curIsText = dynamic_cast<DrawingText*>(e);
        if(curIsText)
        {
            TextItemPropertySetter* setter = ui->imageFrame->interfaceOfTextManager();
            setter->setText(val);
            setter->setProperty(curIsText);
            curIsText->update();
        }
    }
}


// 处理大小，颜色，透光度
void EditPDF_MainWindow::handleCurrntFocusItem(DrawingFocusing s, int value, QColor c)
{
    QList<QGraphicsItem*> it = ui->imageFrame->sceneInterFace()->selectedItems();
    switch(s)
    {
    case DrawingFocusing::WIDTH:
        {
            for(auto& e : it)
            {
                DrawingText* curIsText = dynamic_cast<DrawingText*>(e);
                if(curIsText)
                {
                    int sizeOfTxt = TextItemPropertySetter::getStringSize(
                                           curIsText->getText(), curIsText->getFont()).width();
                    curIsText->setSize(sizeOfTxt, curIsText->boundingRect().height());
                    curIsText->update();
                    break;
                }

                DrawingRect* curIsRect = dynamic_cast<DrawingRect*>(e);
                if(curIsRect)
                {
                    ui->lineEdit_curLength->setText("长度: " + QString::number(value));
                    curIsRect->setSize(value, curIsRect->boundingRect().height());
                    curIsRect->update();
                }
            }
        }break;
    case DrawingFocusing::HIEGHT:
        {
            for(auto& e : it)
            {
                DrawingText* curIsText = dynamic_cast<DrawingText*>(e);
                if(curIsText)
                {
                    int sizeOfTxt = TextItemPropertySetter::getStringSize(
                                           curIsText->getText(), curIsText->getFont()).height();
                    curIsText->setSize(curIsText->boundingRect().width(), sizeOfTxt);
                    curIsText->update();
                    break;
                }
                DrawingRect* curIsRect = dynamic_cast<DrawingRect*>(e);
                if(curIsRect)
                {
                    ui->lineEdit_curHeight->setText("宽度" + QString::number(value));
                    curIsRect->setSize(curIsRect->boundingRect().width(), value);
                    curIsRect->update();
                }
            }
        }break;
    case DrawingFocusing::COLOR:
        {
            for(auto& e : it)
            {
                DrawingText* curIsText = dynamic_cast<DrawingText*>(e);
                if(curIsText)
                {
                    TextItemPropertySetter* setter = ui->imageFrame->interfaceOfTextManager();
                    setter->setCurrentColor(c);
                    setter->setProperty(curIsText);
                    curIsText->update();
                    updateUiIcon(ui->btn_setColor_text,c);
                    break;
                }
                DrawingRect* curIsRect = dynamic_cast<DrawingRect*>(e);
                if(curIsRect)
                {
                    curIsRect->setColor(c);
                    curIsRect->update();
                    updateUiIcon(ui->btn_setColor,c);
                }
            }
        }
        break;
    case DrawingFocusing::TRANSPARENCY:
        {
            for(auto& e : it)
            {
                DrawingText* curIsText = dynamic_cast<DrawingText*>(e);
                if(curIsText)
                {
                    TextItemPropertySetter* setter = ui->imageFrame->interfaceOfTextManager();
                    setter->setBackGroundColor(curIsText->getColor());
                    setter->setBackGroundTransparency(value);
                    setter->setProperty(curIsText);
                    updateUiIcon(ui->btn_setColor_text,setter->getBackGroundColor());
                    curIsText->update();
                    break;
                }

                DrawingRect* curIsRect = dynamic_cast<DrawingRect*>(e);
                if(curIsRect)
                {
                    MarkerPropertySetter* setter = ui->imageFrame->interfaceOfMarkerManager();
                    setter->setColor(curIsRect->getColor());
                    setter->setTransParency(value);
                    setter->setProperty(curIsRect);
                    updateUiIcon(ui->btn_setColor,setter->getMarkerColor());
                    curIsRect->update();
                }
            }
        }
    break;
        case DrawingFocusing::BACKGROUND_COLOR:
        {
            for(auto& e : it)
            {
                DrawingText* curIsText = dynamic_cast<DrawingText*>(e);
                if(curIsText)
                {
                    ui->imageFrame->interfaceOfTextManager()->setBackGroundColor(c);
                    ui->imageFrame->interfaceOfTextManager()->setProperty(curIsText);
                    curIsText->update();
                }
            }
        }break;
    }
}

bool EditPDF_MainWindow::setAsSave()
{
    savingManager->unsetShellQueryingSave();
    isEditedSave = true;
    return true;
}

bool EditPDF_MainWindow::quit()
{
    this->close();
    return true;
}

QPixmap EditPDF_MainWindow::getEditedImage()
{
    after_edited = QPixmap::fromImage(image);
    QPainter painter(&after_edited);
    painter.fillRect(image.rect(), QBrush(Qt::white));
    ui->imageFrame->sceneInterFace()->render(&painter);   //关键函数
    return after_edited;
}

// 添加荧光笔
bool EditPDF_MainWindow::on_btn_addMarker_clicked()
{
    ui->toolsTab->setCurrentIndex(TAB_MARKER_INDEX);
    isEditedSave = false;
    savingManager->setShellQueryingSave();
    ui->imageFrame->setViewState(PDF_EditGraphicView::FlagState::CREATING_MARKER);
    ui->btn_setColor->setText("设置创建颜色");
    state = FlagState::Creating;
    return true;
}

// 设置透光度
void EditPDF_MainWindow::on_horizontalSlider_transparency_valueChanged(int value)
{
    setDrawingRectTransparency(static_cast<short>(value));
}

void EditPDF_MainWindow::on_horizontalSlider_transparency_text_valueChanged(int value)
{
    setDrawingTextTransparency(static_cast<short>(value));
}

// 设置Rect颜色
void EditPDF_MainWindow::on_btn_setColor_clicked()
{
    QColor usrChoice = ColorManager::getColorFromUserChoice();
    if(usrChoice.isValid())
        setDrawingRectColor(usrChoice);
}

// 设置Text的颜色
void EditPDF_MainWindow::on_btn_setColor_text_clicked()
{
    QColor usrChoice = ColorManager::getColorFromUserChoice();
    if(usrChoice.isValid())
        setDrawingTextColor(usrChoice);
}

// 设置BK Color
void EditPDF_MainWindow::on_btn_setColor_textbackground_clicked()
{
    QColor usrChoice = ColorManager::getColorFromUserChoice();
    if(usrChoice.isValid())
        switch(state)
        {
        case FlagState::Creating:
        case FlagState::Editing:
        {
            ui->btn_setColor_textbackground->setIcon(ColorManager::getPureIcon(usrChoice));
            handleCurrntFocusItem(DrawingFocusing::BACKGROUND_COLOR, 0 , usrChoice);
            break;
        }
        case FlagState::Moving:
            break;
        }
}


// 处理荧光笔的宽度条
void EditPDF_MainWindow::on_horizontalSlider_currentWidth_valueChanged(int value)
{
    switch(state)
    {
    case FlagState::Creating:
    case FlagState::Editing:
    {
        handleCurrntFocusItem(DrawingFocusing::WIDTH, value, QColor());
        break;
    }
    case FlagState::Moving:
        break;
    }
}

// 处理荧光笔的高度条
void EditPDF_MainWindow::on_horizontalSliderCurrentHeight_valueChanged(int value)
{
    switch(state)
    {
    case FlagState::Creating:
    case FlagState::Editing:
    {
        handleCurrntFocusItem(DrawingFocusing::HIEGHT, value, QColor());
        break;
    }
    case FlagState::Moving:
        break;
    }
}

bool EditPDF_MainWindow::on_btn_addText_clicked()
{
    ui->toolsTab->setCurrentIndex(TAB_TEXT_INDEX);
    isEditedSave = false;
    savingManager->setShellQueryingSave();
    ui->imageFrame->setViewState(PDF_EditGraphicView::FlagState::CREATING_TEXT);
    ui->btn_setColor_text->setText("设置创建颜色");
    state = FlagState::Creating;
    return true;
}

EditPDF_MainWindow::~EditPDF_MainWindow()
{
    delete savingManager;
    delete ui;
}

void EditPDF_MainWindow::on_textEditPlace_textChanged()
{
    handleCurrntFocusItem(DrawingFocusing::WIDTH, 0, QColor());
    handleCurrntFocusItem(DrawingFocusing::HIEGHT, 0, QColor());
    handleCurrentFocusTextSize(ui->textEditPlace->toPlainText());
}

void EditPDF_MainWindow::on_btn_setColor_textfont_clicked()
{
    handleCurrentFocusTextFont(TextFontManager::getFontFromUserChoice());
}

void EditPDF_MainWindow::on_rermove_selected_clicked()
{
    removeTheSelectedItems();
}

void EditPDF_MainWindow::on_btn_resumeLastOperation_clicked()
{
    resumeLastState();
}


void EditPDF_MainWindow::on_btn_resumeLastResume_clicked()
{
    resumeLastResume();
}


void EditPDF_MainWindow::on_Edited_toolBox_currentChanged(int index)
{
    if(index == IS_SAVE_TOOLBOX_INDEX)
    {
        ui->image_res_label->setPixmap(getEditedImage().scaled(ui->image_res_label->size(), Qt::KeepAspectRatio));
    }
}

void EditPDF_MainWindow::on_btn_refresh_clicked()
{
    ui->image_res_label->setPixmap(getEditedImage().scaled(ui->image_res_label->size(), Qt::KeepAspectRatio));
}

void EditPDF_MainWindow::on_btn_save_clicked()
{
    getEditedImage();
}


void EditPDF_MainWindow::on_toolsTab_tabBarClicked(int index[[maybe_unused]])
{
    backToEditingMode();
}

void EditPDF_MainWindow::on_remove_all_clicked()
{
    removeAllItems();
}




