#ifndef glbMgunner
#define glbMgunner
#include "glbBot.h" 
#include "glbData.h"

class Mgunner: public Bot{ // clasas derivata pentru bot
private:
    int protector;
public:
    Mgunner(int x, int y): Bot(500, 400, 1, 10, 90, 60, 30, 20, 2, x, y, 2), protector(0){}
    bool protect(){
        if(protector==0){
            protector=1;
            cshield+=200;
            shield+=200;
            return 1;
        }
        return 0;
    }
    void move(int xn ,int yn, std::vector<std::vector<int>>pos){
        int xm=x, ym=y, j;
        if(xn>x){
            x++;
        }
        else if(xn<x){
            x--;
        }
        if(yn<y){
            y--;
        }
        else if(yn>y){
            y++;
        }
        if(100<x){
            x=100;
        }
        else if(x<0){
            x=0;
        }
        if(100<y){
            y=100;
        }
        else if(y<0){
            y=0;
        }
        for(int i=0; i<pos.size(); i++){
            if(pos[i][0] == x && pos[i][1] == y){
                x=xm;
                y=ym;
            }
        }
        pos[id][0]=x;
        pos[id][1]=y;
    }
    ~Mgunner(){
        std::vector<std::vector<int*>> &pos = *Data::getData().Pos();
        pos[id][0] = new int(101);
        pos[id][1] = new int(101);
        if(id<8)
            Data::getData().Team1()->erase(std::find(Data::getData().Team1()->begin(), Data::getData().Team1()->end(), this));
        else
            Data::getData().Team2()->erase(std::find(Data::getData().Team2()->begin(), Data::getData().Team2()->end(), this));
    }
};

#endif