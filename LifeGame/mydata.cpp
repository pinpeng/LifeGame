#include "mydata.h"

MyData::MyData(int lineCount, int columnCount)
    :cellMap(lineCount,QVector<bool>(columnCount,false)){
}

bool MyData::isLive(int x, int y) const
{
    return cellMap[x][y];
}

void MyData::setCellDead(int x, int y)
{
    cellMap[x][y] = false;
}

void MyData::setCellLive(int x, int y)
{
    cellMap[x][y] = true;
}

int MyData::getLineCount() const
{
    return cellMap.size();
}

int MyData::getColumnCount() const
{
    return cellMap[0].size();
}

//void MyData::clear()
//{
//    for(auto&i:cellMap)
//        std::fill(i.begin(),i.end(),false);
//}
