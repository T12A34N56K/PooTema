#ifndef glbBot
#define glbBot
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

class Bot{
protected:
    int health, shield, speed, rpt, acuracy1, acuracy2, acuracy3, damage, setup, x, y, cls, id, chealth, cshield;
    static int idn;
    static std::vector<std::vector<Bot*>> TTT1;
    static std::vector<std::vector<Bot*>> TTT2;
    static std::vector<int> TCT1;
    static std::vector<int> TCT2;
    std::vector<std::vector<Bot*>> PT;
    std::vector<int> PC;
public:
    int getId(){
        return id;
    }
    Bot(int h, int s1, int s2, int rpm, int a1, int a2, int a3, int d, int s3, int x, int y, int cls): health(h), shield(s1), speed(s2), rpt(rpm), acuracy1(a1), acuracy2(a2), acuracy3(a3), damage(d), setup(s3), x(x), y(y), cls(cls), id(idn++), chealth(h), cshield(s1){}
    void shoot(Bot *tinta, int ign=0){
        int dist=sqrt((tinta->getX()-x)*(tinta->getX()-x)+(tinta->getY()-y)*(tinta->getY()-y))/5, ac=0, dmg=0;
        if(dist==0){
            ac=acuracy1;
        }
        else if(dist==1){
            ac=acuracy2;
        }
        else if(dist==2){
            ac=acuracy3;
        }
        for(int j=0; j<rpt; j++){
            int i=rand()%100;
            if(ac>i){
                dmg+=damage;
            }
        }
        tinta->takeDmg(dmg, ign);
    }
    void stats(){
        std::cout<<"\n\nid: "<<id;
        std::cout<<"\nclass: "<<cls;
        std::cout<<"\nShields: "<<cshield<<"/"<<shield;
        std::cout<<"\nHealth: "<<chealth<<"/"<<health;
        std::cout<<"\nX: "<<x<<" Y: "<<y;
    }
    virtual void move(int xn ,int yn, std::vector<std::vector<int*>>&pos){
        int xm=x, ym=y, j;
        if(xn>x){
            xm++;
        }
        else if(xn<x){
            xm--;
        }
        if(yn<y){
            ym--;
        }
        else if(yn>y){
            ym++;
        }
        if(xm>50){
            xm=50;
        }
        else if(xm<0){
            xm=0;
        }
        if(ym>50){
            ym=50;
        }
        else if(ym<0){
            ym=0;
        }
        for(int i=0; i<pos.size(); i++){
            if(*pos[i][0] == xm && *pos[i][1] == ym){
                return;
            }
        }
        x=xm;
        y=ym;
    }
    int getClass(){
        return cls;
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    int *pGetX(){
        return &x;
    }
    int *pGetY(){
        return &y;
    }
    int getShield(){
        return cshield;
    }
    int getHealth(){
        return chealth;
    }
    bool takeDmg(int dmg, int ignshld){
        if(cshield>0 && !ignshld){
            cshield-=dmg;
            if(cshield<0){
                chealth+=cshield;
                cshield=0;
            }
        }
        else if(chealth>0){
            chealth-=dmg;
        }
        if(chealth<=0){
            delete this;
            return 1;
        }
        return 0;
    }
    virtual ~Bot(){
        std::cout<<"BotDown!";
    }
};

inline int Bot::idn=0;

#endif