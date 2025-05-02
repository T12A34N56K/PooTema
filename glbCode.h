#ifndef glbCode
#define glbCode
#include "glbBot.h"
#include "glbData.h"
#include "glbMgunner.h"
#include "glbActiune.h"
#include "glbFread.h"
#include <string>
#include <algorithm>

class Code{
protected:
    std::vector<std::string> tclass;
    int minh=-1, maxh=-1, mins=-1, maxs=-1, minsh=-1, maxsh=-1, ttc, ptc, aliance, dist1=0, dist2=0, dist3=0, adist=0;
    std::vector<int>tt;
    std::vector<int>pt;
public:
    Code operator=(const Code &cod){
        if(this!=&cod){
            this->tclass=cod.tclass;
            this->minh=cod.minh;
            this->maxh=cod.maxh;
            this->mins=cod.mins;
            this->maxs=cod.maxs;
            this->minsh=cod.minsh;
            this->maxsh=cod.maxsh;
            this->ttc=cod.ttc;
            this->ptc=cod.ptc;
            this->aliance=cod.aliance;
            this->dist1=cod.dist1;
            this->dist2=cod.dist2;
            this->dist3=cod.dist3;
            this->adist=cod.adist;
            this->tt=cod.tt;
            this->pt=cod.pt;
        }
        return *this;
    }
    virtual void craeteTree(Bot* tinta){
        std::string adaus;
        Fread::fRead(adaus);
        if(adaus=="class("){
            while(true){
                Fread::fRead(adaus);
                if(adaus==")"){
                    break;
                }
                tclass.push_back(adaus);
            }
            Fread::fRead(adaus);
        }
        if(adaus=="h"){
            Fread::fRead(maxh);
            Fread::fRead(minh);
            Fread::fRead(adaus);
            }
        if(adaus=="s"){
            Fread::fRead(mins);
            Fread::fRead(maxs);
            Fread::fRead(adaus);
        }
        if(adaus=="sh"){
            Fread::fRead(minsh);
            Fread::fRead(maxsh);
            Fread::fRead(adaus);
        }
        if(adaus=="dist1"){
            dist1=1;
            Fread::fRead(adaus);
        }
        if(adaus=="dist2"){
            dist2=1;
            Fread::fRead(adaus);
        }
        if(adaus=="dist3"){
            dist3=1;
            Fread::fRead(adaus);
        }
        if(adaus=="adist"){
            adist=1;
            Fread::fRead(adaus);
        }
        if(adaus=="me"){
            aliance=0;
        }
        else if(adaus=="ei"){
            if(tinta->getId()<8){
                aliance=2;
            }
            else{
                aliance=1;
            }
        }
        else if(adaus=="noi"){
            if(tinta->getId()<8){
                aliance=1;
            }
            else{
                aliance=2;
            }
        }
        else if(adaus=="toti"){
            aliance=3;
        }
    }
    virtual std::vector<Bot*> verBot(Bot* tinta, const std::vector<Bot*> &lista){
        std::vector<Bot*>tinte;
        if(tclass.size()){
            for(auto i : tclass){
                int k=2;
                if(i == "Sniper"){
                    k=4;
                }
                else if(i == "Bracher"){
                    k=3;
                }
                else if(i == "Riflemen"){
                    k=1;
                }
                for(auto j : lista){
                    if(j->getClass()==k){
                        tinte.push_back(j);
                    }
                }
            }
        }
        else{
            tinte=lista;
        }
        if(dist1 || dist2 || dist3 || adist){
            for(int i=0; i<tinte.size(); i++){
                if(!dist1 && !sqrt(pow(tinta->getX() - tinte[i]->getX(), 2) + pow(tinta->getY() - tinte[i]->getY(), 2))/5){
                    tinte.erase(tinte.begin()+i);
                    i--;
                }
                else if(!dist2 && sqrt(pow(tinta->getX() - tinte[i]->getX(), 2) + pow(tinta->getY() - tinte[i]->getY(), 2))/5==1){
                    tinte.erase(tinte.begin()+i);
                    i--;
                }
                else if(!dist3 && sqrt(pow(tinta->getX() - tinte[i]->getX(), 2) + pow(tinta->getY() - tinte[i]->getY(), 2))/5==2){
                    tinte.erase(tinte.begin()+i);
                    i--;
                }
                else if(!adist && sqrt(pow(tinta->getX() - tinte[i]->getX(), 2) + pow(tinta->getY() - tinte[i]->getY(), 2))/5>2){
                    tinte.erase(tinte.begin()+i);
                    i--;
                }
            }
        }
        for (auto i : tinte){
            if(minh>=0 && maxh>=minh){
                if(!(minh<=i->getHealth() && i->getHealth()<=maxh)){
                    tinte.erase(std::find(tinte.begin(), tinte.end(), i));
                }
            }
            if(mins>=0 && maxs>=mins){
                if(!(mins<=i->getShield() && i->getShield()<=maxs)){
                    tinte.erase(std::find(tinte.begin(), tinte.end(), i));
                }
            }
            if(minsh>=0 && maxsh>=minsh){
                if(!(minsh<=(i->getHealth() + i->getShield()) && (i->getHealth() + i->getShield())<=maxsh)){
                    tinte.erase(std::find(tinte.begin(), tinte.end(), i));
                }
            }
        }
        return tinte;
    }
    virtual bool operator()(Bot* tinta){return 1;}
};

#endif