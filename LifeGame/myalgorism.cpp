#include "myalgorism.h"
#include <ctime>

void MyAlgorism::randomCell(int numCount)
{
    srand(time(0));
    int lineCount = data[flag]->getLineCount();
    int columnCount = data[flag]->getColumnCount();

    for(int i=0;i<numCount;++i){
        int tempX = rand()%lineCount;
        int tempY = rand()%columnCount;
        data[flag]->setCellLive(tempX,tempY);
    }
}

int MyAlgorism::getRoundCount(int x, int y)
{
    int ans = 0;
    for(int i=x-1;i<=x+1;++i){
        for(int j=y-1;j<=y+1;++j){
            if(i<0||i>=data[flag]->getLineCount()) continue;
            if(j<0||j>=data[flag]->getColumnCount()) continue;
            ans += (data[flag]->isLive(i,j)?1:0);
        }
    }
    return ans-(data[flag]->isLive(x,y)?1:0);
}

bool MyAlgorism::judgeCellLive(int x,int y,int count)
{
    if(count<2) return false;
    if(count>3) return false;
    if(count==3) return true;

    return data[flag]->isLive(x,y);
}

void MyAlgorism::switchFlag()
{
    flag ^= 1;
}

MyAlgorism::MyAlgorism(int lineCount, int columnCount,int cellCount,double cellWidth,double cellHeight)
    :data(2,nullptr),flag(false),cellWidth(cellWidth),cellHeight(cellHeight)
{
    data[0] = new MyData(lineCount,columnCount);
    data[1] = new MyData(lineCount,columnCount);

    randomCell(cellCount);
}

MyAlgorism::~MyAlgorism()
{
    if(data[0]){
        delete data[0];
        data[0] = nullptr;
    }
    if(data[1]){
        delete data[1];
        data[1] = nullptr;
    }
}

void MyAlgorism::updateMyData()
{
    for(int i=0;i<data[flag]->getLineCount();++i){
        for(int j=0;j<data[flag]->getColumnCount();++j){
            if(judgeCellLive(i,j,getRoundCount(i,j)))
                data[!flag]->setCellLive(i,j);
            else
                data[!flag]->setCellDead(i,j);
        }
    }

    switchFlag();
}

int MyAlgorism::getColumnCount()
{
    return data[flag]->getColumnCount();
}

int MyAlgorism::getLineCount()
{
    return data[flag]->getLineCount();
}

const MyData &MyAlgorism::getData() const
{
    return *(data[flag]);
}

double MyAlgorism::getCellWidth() const
{
    return cellWidth;
}

double MyAlgorism::getCellHeight() const
{
    return cellHeight;
}
