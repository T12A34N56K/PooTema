#ifndef glbBot
#define glbBot
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

class Bot{ // clasas de baza bot
protected: //statisticile
    int health, shield, speed, rpt, acuracy1, acuracy2, acuracy3, damage, setup, x, y, cls, id, chealth, cshield;
    static int idn;
    static std::vector<std::vector<Bot*>> TTT1;
    static std::vector<std::vector<Bot*>> TTT2;
    static std::vector<int> TCT1;
    static std::vector<int> TCT2;
    std::vector<std::vector<Bot*>> PT;
    std::vector<int> PC;
public:
    int getId(){ //id getter
        return id;
    }
    //constructor
    Bot(int h, int s1, int s2, int rpm, int a1, int a2, int a3, int d, int s3, int x, int y, int cls): health(h), shield(s1), speed(s2), rpt(rpm), acuracy1(a1), acuracy2(a2), acuracy3(a3), damage(d), setup(s3), x(x), y(y), cls(cls), id(idn++), chealth(h), cshield(s1){}
    virtual Bot *clone() const = 0;
    void shoot(Bot *tinta, int ign=0){ // functia de tras
        int dist=sqrt((tinta->getX()-x)*(tinta->getX()-x)+(tinta->getY()-y)*(tinta->getY()-y))/5, ac=0; //afla distanta
        if(dist==0){ //seteaza precizia
            ac=acuracy1;
        }
        else if(dist==1){
            ac=acuracy2;
        }
        else if(dist==2){
            ac=acuracy3;
        }
        for(int j=0; j<rpt; j++){ //calculeaza daunele
            int i=rand()%100;
            if(ac>i){
                try{
                    tinta->takeDmg(damage, ign); //creaza daunele
                }
                catch (int &i){
                    std::cout<<"catch: "<<i;
                    break;
                }
            }
        }
    }
    void stats(){ // printarea statisticilor
        std::cout<<"\n\nid: "<<id;
        std::cout<<"\nclass: "<<cls;
        std::cout<<"\nShields: "<<cshield<<"/"<<shield;
        std::cout<<"\nHealth: "<<chealth<<"/"<<health;
        std::cout<<"\nX: "<<x<<" Y: "<<y;
    }
    virtual void move(int xn ,int yn, std::vector<std::vector<int*>>&pos){ // functia de move
        int xm=x, ym=y, j;
        if(xn>x){ // schimba x-ul si y-ul
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
        for(int i=0; i<pos.size(); i++){ //daca se afla cineva acolo, nu face schimbarile
            if(*pos[i][0] == xm && *pos[i][1] == ym){
                return;
            }
        }
        x=xm; //altfel le face
        y=ym;
    }
    int getClass(){ // geteri
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
    void takeDmg(int dmg, int ignshld){ // take dmg
        if(cshield>0 && !ignshld){ // verifica daca mai are ce scuturi
            cshield-=dmg; // ia damage
            if(cshield<0){ // daca a ramas fara scuturi
                chealth+=cshield; //transfera daunele la viata
                cshield=0;
            }
        }
        else if(chealth>0){ // altfel da la viata
            chealth-=dmg;
        }
        if(chealth<=0){ // daca nu mai are viata
            delete this; // moare
            std::cout<<"before";
            throw chealth;
            std::cout<<"after";
        }
    }
    virtual ~Bot(){ // destructor virtual
        std::cout<<"BotDown!\n";
    }
};

inline int Bot::idn=0;

#endif