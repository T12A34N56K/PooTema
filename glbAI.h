#ifndef glbAI
#define glbAI
#include "glbActiune.h"
#include "glbBot.h"
#include "glbConditie.h"
#include "glbFread.h"
#include <iostream>
#include <vector>
#include <string>

class AI{
private:
    std::vector<Code*> cod;
    Bot* bot;
    int id;
    void genAI(){
        Fread::fOpen("glbAItest.in");
        int x;
        Fread::fRead(x);
        for(int i=0; i<x; i++){
            std::string nou;
            Fread::fRead(nou);
            if(nou=="actiune"){
                Actiune *acti = new Actiune();
                acti->createTree(bot);
                cod.push_back(acti->codePtr());
            }
            else{
                Conditie *ncd = new Conditie();
                ncd->craeteTree(bot);
                cod.push_back(ncd);
            }
        }
        Fread::fClose();
    }
public:
    void getStats(){
        bot->stats();
    }
    AI(Bot* bot):bot(bot){
        genAI();
        id=bot->getId();
    }
    int getId(){
        return id;
    }
    void think(){
        for(auto i:cod){
            if(i->operator()(bot))
                break;
        }
    }
};

#endif