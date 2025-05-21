#include "glbActiune.h"
#include "glbMgunner.h"
#include "glbData.h"
#include "glbCode.h"
#include "glbFread.h"
#include <math.h>
#include <memory>

class ActualActiune: public Code{ // implementarea clasei actiune
private:
    int dist, act; // noi variabile pentru apropiere si actiune
public:
    void setDist(int ndist){
        dist=ndist;
    }
    void setAct(int nact){
        act=nact;
    }
    void craeteTree(Bot* tinta){
        Code::craeteTree(tinta); // conditiile vechi
        std::string adaus;
        Fread::fRead(adaus); // la care se adauga ceva nou

        if(adaus=="dist"){
            Fread::fRead(dist);
            Fread::fRead(adaus);
        }
        if(adaus=="act"){
            Fread::fRead(act);
        }
    }
    std::vector<Bot*> verBot(Bot* tinta, const std::vector<Bot*> &lista){
        std::vector<Bot*> tinte = Code::verBot(tinta, lista); // verificarea veche
        Bot *tintaf;
        if(dist==1){ // din care se alege doar un element
            float d=sqrt(2*50*51);
            for(auto i : tinte){
                float d1=sqrt(pow(tinta->getX()-i->getX(), 2)+pow(tinta->getX()-i->getY(), 2));
                if(d1<d){
                    d == d1;
                    tintaf=i;
                }
            }
        }
        else{
            float d=0;
            for(auto i : tinte){
                float d1=sqrt(pow(2, i->getX())+pow(2, i->getY()));
                if(d1>d){
                    d == d1;
                    tintaf=i;
                }
            }
        }
        if(act==1){ // asupra caruia se actioneaza
            tinta->shoot(tintaf);
            return {tintaf};
        }
        else if(act==2){
            tinta->move(tintaf->getX(), tintaf->getY(), *Data::getData().Pos());
            return {tintaf};
        }
        else if(act==3){
            tinta->move(tinta->getX()+(tinta->getX()-tintaf->getX()), tinta->getY()+(tinta->getY()-tintaf->getY()), *Data::getData().Pos());
            return {tintaf};
        }
        else if(act==4){
            if(tinta->getClass()==1){
                Mgunner *mg = dynamic_cast<Mgunner*>(tinta);
                if(mg->protect()){
                    return {tintaf};
                }
            }
        }
        return {};
    }
    bool operator()(Bot* tinta){
        std::vector<Bot*> lista; // lista de tinte
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
        std::vector<Bot*> x = verBot(tinta, lista); // care se verifica
        if(x.size()){
            return 1;
        }
        return 0;
    }
};

Actiune::Actiune(): code_(new ActualActiune()){} // constructor pentru actiune normal
void Actiune::setDist(int ndist){ // functi care au rolul de a pointa catre functi din ActualActiune
    if(auto* act = dynamic_cast<ActualActiune*>(code_.get())){
        act->setDist(ndist);
    }
}
void Actiune::setAct(int nact){
    if(auto* act = dynamic_cast<ActualActiune*>(code_.get())){
        act->setAct(nact);
    }
}
std::vector<Bot*> Actiune::verBot(Bot* tinta, const std::vector<Bot*> &lista){
    return code_->verBot(tinta, lista);
}
bool Actiune::operator()(Bot* tinta){
    return code_->operator()(tinta);
}
Code* Actiune::codePtr(){
    return code_.get();
}
void Actiune::createTree(Bot* tinta){
    code_->craeteTree(tinta);
}