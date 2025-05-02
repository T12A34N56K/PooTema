#ifndef glbData
#define glbData
#include "glbBot.h"


class Data{
protected:
    Data(){}; // constructor privat deoarece siingleton
    std::vector<Bot*> team1, team2; // vectori cu cele 2 echipe
    std::vector<std::vector<int*>>pos; // vector cu coord x y ale tuturor
public:
    static Data& getData(){ // pentru a accesa singletonul
        static Data data;
        return data;
    }
    std::vector<Bot*> *Team1(){
        return &team1;
    }
    std::vector<Bot*> *Team2(){
        return &team2;
    }
    std::vector<std::vector<int*>> *Pos(){
        return &pos;
    }
    ~Data(){}
};

#endif