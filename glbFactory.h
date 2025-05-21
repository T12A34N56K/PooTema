#include "glbBreacher.h"
#include "glbMgunner.h"
#include "glbRiflemen.h"
#include "glbSniper.h"

class Factory{
public:
    virtual ~Factory(){}
    virtual Bot* FactoryMethod(int x, int y) const = 0;
};

class CreateBreacher: public Factory{
public:
    Bot* FactoryMethod(int x, int y) const override{
        return new Breacher(x, y);
    }
};

class CreateMgunner: public Factory{
public:
    Bot* FactoryMethod(int x, int y) const override{
        return new Mgunner(x, y);
    }
};

class CreateRiflemen: public Factory{
public:
    Bot* FactoryMethod(int x, int y) const override{
        return new Riflemen(x, y);
    }
};

class CreateSniper: public Factory{
public:
    Bot* FactoryMethod(int x, int y) const override{
        return new Sniper(x, y);
    }
};