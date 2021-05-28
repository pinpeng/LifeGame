#ifndef MYALGORISM_H
#define MYALGORISM_H

#include "mydata.h"

class MyAlgorithm
{
private:
    QVector<MyData*> data;
    bool flag;  //flag为false时用第一个，flag为true时用第二个
    double cellWidth,cellHeight;
private:
    void randomCell(int numCount);
    int getRoundCount(int x,int y);
    bool judgeCellLive(int x,int y,int count);
    void switchFlag();
public:
    MyAlgorithm(int lineCount,int columnCount,int cellCount,double cellWidth,double cellHeight);
    ~MyAlgorithm();

    void updateMyData();
    int getLineCount();
    int getColumnCount();
    const MyData& getData() const;
    double getCellWidth() const;
    double getCellHeight() const;
};

#endif // MYALGORISM_H
