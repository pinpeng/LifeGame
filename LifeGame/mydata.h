#ifndef MYDATA_H
#define MYDATA_H

#include <QVector>

class MyData
{
private:
    QVector<QVector<bool>> cellMap;
public:
    MyData(int lineCount,int columnCount);
    bool isLive(int x,int y) const;
    void setCellDead(int x,int y);
    void setCellLive(int x,int y);
    int getLineCount() const;
    int getColumnCount() const;
//    void clear();
};

#endif // MYDATA_H
