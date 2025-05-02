#ifndef glbActiune
#define glbActiune
#include "glbMgunner.h"
#include "glbData.h"
#include <math.h>
#include <memory>

class Code;

class Actiune{
private:
    std::unique_ptr<Code> code_;
public:
    Actiune();
    void setDist(int ndist);
    void setAct(int nact);
    std::vector<Bot*> verBot(Bot* tinta, const std::vector<Bot*> &lista);
    bool operator()(Bot* tinta);
    Code* codePtr();
    void createTree(Bot* tinta);
};

#endif