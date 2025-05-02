#ifndef glbActiune
#define glbActiune
#include "glbMgunner.h"
#include "glbData.h"
#include <math.h>
#include <memory>

class Code; // forward declare la code

class Actiune{
private:
    std::unique_ptr<Code> code_; // pointer la code
public: //functii ce vor fi definite in .cpp si for pointa la implementare
    Actiune();
    void setDist(int ndist);
    void setAct(int nact);
    std::vector<Bot*> verBot(Bot* tinta, const std::vector<Bot*> &lista);
    bool operator()(Bot* tinta);
    Code* codePtr();
    void createTree(Bot* tinta);
};

#endif