#ifndef glbBreacher
#define glbBreacher
#include "glbBot.h"
#include "glbData.h"

class Breacher: public Bot{
private:
    int sprnt;
public:
    Breacher(int x, int y): Bot(300, 300, 2, 5, 90, 30, 10, 30, 0, x, y, 3), sprnt(0){}
    void spdbost(int xn ,int yn, std::vector<std::vector<int*>>&pos){
        if(sprnt<3){
            sprnt++;
            speed=3;
            Bot::move(xn ,yn, pos);
        }
    }
    ~Breacher(){
        std::vector<std::vector<int*>> &pos = *Data::getData().Pos();
        pos[id][0] = new int(101);
        pos[id][1] = new int(101);
        if(id<8)
            Data::getData().Team1()->erase(find(Data::getData().Team1()->begin(), Data::getData().Team1()->end(), this));
        else
            Data::getData().Team2()->erase(find(Data::getData().Team2()->begin(), Data::getData().Team2()->end(), this));
    }
};

#endif