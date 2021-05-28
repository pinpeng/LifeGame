#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPen>
#include <QTimer>
#include "myalgorithm.h"

namespace Ui {
class PaintWidget;
}

class PaintWidget : public QWidget
{
    Q_OBJECT
private:
    int lineCount,columnCount;
    double cubeWidth,cubeHeight;
    int cellCount;
    int isStart;        //0:初始化 1:开始 2:暂停

    QBrush bkgdBrush;
    QBrush cellBrush;
    QPen linePen;

    MyAlgorithm *algorithm;
    QTimer timer;
    Ui::PaintWidget *ui;
private:
//    void printSettings();
    void initTimer();

    void paintEvent(QPaintEvent *event) override;
    void paintBkGround(QPainter& painter);
    void paintLines(QPainter& painter);
    void paintInitLines(QPainter& painter);
    void paintStartLines(QPainter& painter);
    void paintCube(QPainter& painter);

    void setState(int val);
    int getState();
public:
    explicit PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget();
private slots:
    void onTimeOut();
public slots:
    void setLineCount(int lineCount);
    void setColumnCount(int columnCount);
    void setCellCount(int cellCount);
    void setDeltaTime(int speed);

    void onStartClicked();
    void onPauseClicked();
    void onNextTurnClicked();
    void onClearClicked();

signals:
    void sendState(int state);
};

#endif // PAINTWIDGET_H
