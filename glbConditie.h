#ifndef glbConditie
#define glbConditie
#include "glbCode.h"
#include "glbData.h"
#include "glbFread.h"

class Conditie: public Code{
    int exista;
    std::vector<Code*> cont;
public:
    void craeteTree(Bot* tinta){
        Code::craeteTree(tinta);
        std::string adaus;
        Fread::fRead(adaus);
        if(adaus=="exista"){
            exista=1;
        }
        else if(adaus=="nexista"){
            exista=0;
        }
        int x;
        Fread::fRead(x);
        for(int i=0; i<x; i++){
            std::string objtype;
            Fread::fRead(objtype);
            if(objtype == "actiune"){
                Actiune *acti= new Actiune();
                cont.push_back(acti->codePtr());
                acti->createTree(tinta);
            }
            else{
                Code *cod= new Code();
                cont.push_back(cod);
                cod->craeteTree(tinta);
            }
        }
    }
    bool operator()(Bot* tinta){
        std::vector<Bot*> lista;
        if(aliance==0){
            lista.push_back(tinta);
        }
        else if(aliance==1){
            lista=*Data::getData().Team1();
        }
        else if (aliance==2){
            lista=*Data::getData().Team2();
        }
        else if(aliance==3){
            lista=*Data::getData().Team1();
            lista.insert(lista.end(), Data::getData().Team2()->begin(), Data::getData().Team2()->end());
        }
        std::vector<Bot*> x = verBot(tinta, lista);
        if(x.size()){
            return 1;
        }
        return 0;
    }
    std::vector<Bot*> verBot(Bot* tinta, const std::vector<Bot*> &lista){
        std::vector<Bot*> ret = Code::verBot(tinta, lista);
        bool x=0;
        if(exista){
            if(ret.size()){
                for(auto i : cont){
                    x = i->operator()(tinta);
                    if(x){
                        return ret;
                    }
                }
            }
            return {};
        }
        else{
            if(!ret.size()){
                for(auto i : cont){
                    x = i->operator()(tinta);
                    if(x){
                        return {tinta};
                    }
                }
            }
            return {};
        }
    }
};

#endif