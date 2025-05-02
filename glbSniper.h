#ifndef glbSniper
#define glbSniper
#include "glbBot.h"
#include "glbData.h"

class Sniper: public Bot{
private:
    int apr;
public:
    Sniper(int x, int y): Bot(200, 100, 1, 1, 100, 100, 100, 150, 1, x, y, 4), apr(0){}
    void ap(Bot* tinta){
        if(apr==0){
            apr=1;
            Bot::shoot(tinta, 1);
        }
    }
    ~Sniper(){
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