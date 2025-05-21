#ifndef glbRiflemen
#define glbRiflemen
#include "glbBot.h"
#include "glbData.h"

class Riflemen: public Bot{ // clasas derivata pentru bot
public:
    Riflemen(int x, int y):  Bot(300, 300, 2, 5, 90, 30, 10, 30, 0, x, y, 1){}
    Bot *clone() const override{
        return new Riflemen(*this);
    }
    void mns(int xn ,int yn, std::vector<std::vector<int*>>&pos, Bot* tinta){
        Bot::move(xn, yn, pos);
        Bot::shoot(tinta);
    }
    ~Riflemen(){
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