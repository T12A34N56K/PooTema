#ifndef glbAI
#define glbAI
#include "glbActiune.h"
#include "glbBot.h"
#include "glbConditie.h"
#include "glbFread.h"
#include <iostream>
#include <vector>
#include <string>

class AI{ //clasa care se va ocupa de n
private:
    std::vector<Code*> cod;
    Bot* bot;
    int id;
    void genAI(){ //functie care creaza code-ul 
        Fread::fOpen("glbAItest.in"); //deschide fisierul de citire
        int x;
        Fread::fRead(x); //citeste cati "fii" are
        for(int i=0; i<x; i++){
            std::string nou;
            Fread::fRead(nou); //si daca face o actiune sau o cond
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
    void getStats(){ //printarea de la finalul rundei
        bot->stats();
    }
    AI(Bot* bot):bot(bot){ //constructorul
        genAI();
        id=bot->getId();
    }
    int getId(){ //un geter banal
        return id;
    }
    void think(){ //executia programului fiecarui bot
        for(auto i:cod){ //pentru fiecare fiu
            if(i->operator()(bot)) //daca a actionat
                break; //ai terminat
        }
    }
};

#endif