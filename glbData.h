#ifndef glbData
#define glbData
#include "glbBot.h"


class Data{
protected:
    Data(){};
    std::vector<Bot*> team1, team2;
    std::vector<std::vector<int*>>pos;
public:
    static Data& getData(){
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