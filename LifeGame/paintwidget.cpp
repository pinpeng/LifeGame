#include "paintwidget.h"
#include "ui_paintwidget.h"
#include <QPainter>

#include <QDebug>

#define SUM_TIME 1000
#define IS_INIT  0
#define IS_START 1
#define IS_PAUSE 2

void PaintWidget::setLineCount(int lineCount)
{
    this->lineCount = lineCount;
    cubeHeight = height()*1.0f/lineCount;
}

void PaintWidget::setColumnCount(int columnCount)
{
    this->columnCount = columnCount;
    cubeWidth = width()*1.0f/columnCount;
}

void PaintWidget::setCellCount(int cellCount)
{
    this->cellCount = cellCount;
}

void PaintWidget::setDeltaTime(int speed)
{
    if(speed==0)
        return;

    timer.setInterval(1000/speed);
}

void PaintWidget::onStartClicked()
{
    if(algorism) delete algorism;

    algorism = new MyAlgorism(lineCount,columnCount,cellCount,cubeWidth,cubeHeight);

    setState(IS_START);
    repaint();
}

void PaintWidget::onPauseClicked()
{
    if(getState()==IS_START){
        setState(IS_PAUSE);
    }
    else if(getState()==IS_PAUSE){
        setState(IS_START);
    }
}

void PaintWidget::onNextTurnClicked()
{
    setState(IS_PAUSE);
    algorism->updateMyData();

    repaint();
}

void PaintWidget::onClearClicked()
{
    setState(IS_INIT);
    if(algorism) delete algorism;
    algorism = nullptr;

    repaint();
}

//void PaintWidget::printSettings()
//{
//    qDebug()<<"lineCount = "<<lineCount<<endl;
//    qDebug()<<"columnCount = "<<columnCount<<endl;
//    qDebug()<<"cellCount = "<<cellCount<<endl;
//    qDebug()<<"speed = "<<1000/timer.interval()<<endl;
//}

void PaintWidget::initTimer()
{
    timer.start(1000);
    connect(&timer,&QTimer::timeout,this,&PaintWidget::onTimeOut);
}

void PaintWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    paintBkGround(painter);
    paintCube(painter);
    paintLines(painter);

}

void PaintWidget::paintBkGround(QPainter &painter)
{
    painter.fillRect(rect(),bkgdBrush);
}

void PaintWidget::paintLines(QPainter &painter)
{
    if(getState()==IS_INIT){
        paintInitLines(painter);
    }
    else{
        paintStartLines(painter);
    }
}

void PaintWidget::paintInitLines(QPainter &painter)
{
    for(int i=0;i<lineCount;++i)
        painter.drawLine(0,i*cubeHeight,rect().right(),i*cubeHeight);

    for(int i=0;i<columnCount;++i)
        painter.drawLine(i*cubeWidth,0,i*cubeWidth,rect().bottom());

    painter.drawLine(0,rect().bottom(),rect().right(),rect().bottom());
    painter.drawLine(rect().right(),0,rect().right(),rect().bottom());
}

void PaintWidget::paintStartLines(QPainter &painter)
{
    for(int i=0;i<algorism->getLineCount();++i)
        painter.drawLine(0,i*algorism->getCellHeight(),rect().right(),i*algorism->getCellHeight());

    for(int i=0;i<algorism->getColumnCount();++i)
        painter.drawLine(i*algorism->getCellWidth(),0,i*algorism->getCellWidth(),rect().bottom());

    painter.drawLine(0,rect().bottom(),rect().right(),rect().bottom());
    painter.drawLine(rect().right(),0,rect().right(),rect().bottom());
}

void PaintWidget::paintCube(QPainter &painter)
{
    if(isStart!=IS_INIT){
        for(int i=0;i<algorism->getLineCount();++i){
            for(int j=0;j<algorism->getColumnCount();++j){
                if(algorism->getData().isLive(i,j)){
                    painter.fillRect(j*algorism->getCellWidth(),i*algorism->getCellHeight()+1,
                                     algorism->getCellWidth(),algorism->getCellHeight(),
                                     cellBrush);
                }
            }
        }
    }
}

void PaintWidget::setState(int val)
{
    isStart = val;

    emit sendState(val);
}

int PaintWidget::getState()
{
    return isStart;
}

PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent),
    isStart(IS_INIT),
    bkgdBrush(Qt::white),
    cellBrush(Qt::yellow),
    linePen(Qt::black),
    algorism(nullptr),
    timer(this),
    ui(new Ui::PaintWidget)
{
    ui->setupUi(this);

    initTimer();
}

PaintWidget::~PaintWidget()
{
    delete ui;
}

void PaintWidget::onTimeOut()
{
//    printSettings();
    if(getState() == IS_START){
        algorism->updateMyData();
    }
    repaint();
}


