#include "widget.h"
#include "ui_widget.h"

void Widget::initItems()
{
    initColumnCountBox();
    initLineCountBox();
    initCellCountBox();
    initSpeedBox();
    initCellCountSlider();
    initSpeedSlider();

    initStartButton();
    initPauseButton();
    initNextTurnButton();
    initClearButton();
}

void Widget::initColumnCountBox()
{
    connect(ui->columnCountBox,SIGNAL(valueChanged(int)),ui->paintWidget,SLOT(setColumnCount(int)));

    ui->columnCountBox->setRange(1,100);
    ui->columnCountBox->setValue(50);
}

void Widget::initLineCountBox()
{
    connect(ui->lineCountBox,SIGNAL(valueChanged(int)),ui->paintWidget,SLOT(setLineCount(int)));

    ui->lineCountBox->setRange(1,100);
    ui->lineCountBox->setValue(50);
}

void Widget::initCellCountBox()
{
    connect(ui->cellCountBox,SIGNAL(valueChanged(int)),ui->paintWidget,SLOT(setCellCount(int)));
    connect(ui->cellCountBox,SIGNAL(valueChanged(int)),ui->cellCountSlider,SLOT(setValue(int)));

    ui->cellCountBox->setRange(0,10000);
    ui->cellCountBox->setValue(1250);
}

void Widget::initSpeedBox()
{
    connect(ui->speedBox,SIGNAL(valueChanged(int)),ui->paintWidget,SLOT(setDeltaTime(int)));
    connect(ui->speedBox,SIGNAL(valueChanged(int)),ui->speedSlider,SLOT(setValue(int)));

    ui->speedBox->setRange(1,20);
    ui->speedBox->setValue(10);
}

void Widget::initCellCountSlider()
{
    connect(ui->cellCountSlider,SIGNAL(valueChanged(int)),ui->cellCountBox,SLOT(setValue(int)));

    ui->cellCountSlider->setRange(0,10000);
    ui->cellCountSlider->setValue(1250);
}

void Widget::initSpeedSlider()
{
    connect(ui->speedSlider,SIGNAL(valueChanged(int)),ui->speedBox,SLOT(setValue(int)));

    ui->speedSlider->setRange(1,20);
    ui->speedSlider->setValue(10);
}

void Widget::initStartButton()
{
    connect(ui->startButton,&QPushButton::clicked,ui->paintWidget,&PaintWidget::onStartClicked);
}

void Widget::initPauseButton()
{
    connect(ui->pauseButton,&QPushButton::clicked,ui->paintWidget,&PaintWidget::onPauseClicked);
    connect(ui->paintWidget,&PaintWidget::sendState,ui->pauseButton,
            [&](int val){
                if(val==2) ui->pauseButton->setText("继续");
                else ui->pauseButton->setText("暂停");
    }
    );
}

void Widget::initNextTurnButton()
{
    connect(ui->nextTurnButton,&QPushButton::clicked,ui->paintWidget,&PaintWidget::onNextTurnClicked);
}

void Widget::initClearButton()
{
    connect(ui->clearButton,&QPushButton::clicked,ui->paintWidget,&PaintWidget::onClearClicked);
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initItems();

}

Widget::~Widget()
{
    delete ui;
}
