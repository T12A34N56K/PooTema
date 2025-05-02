#include "glbActiune.h"
#include "glbAI.h"
#include "glbBot.h"
#include "glbBreacher.h"
#include "glbCode.h"
#include "glbConditie.h"
#include "glbData.h"
#include "glbFread.h"
#include "glbMgunner.h"
#include "glbRiflemen.h"
#include "glbSniper.h"
#include <iostream>
#include <chrono>
#include <thread>
// using namespace std;

int main(){
    using namespace std::this_thread; //pentru delay-ul de 1 sec
    using namespace std::chrono;

    Data::getData(); //initializez Data
    std::vector<AI> team1, team2; //cele doua echipe care se vor lupta
    team1.reserve(9);
    team2.reserve(9);

    std::cout<<"WeLcome to Gladiobots, AI Combat areana!\n\nYou will have to give the x and y coordenates of 8 Bots, keeping in mind that the arena is a 50x50 grid, and their respective combat classes: 1. Riflemen, 2. MachineGunner, 3. Breacher, 4. Sniper.\n\n";

    for (int i=0; i<8; i++){ //echipa 1
        int x, y, c;
        std::cout<<"Bot "<<i<<" pos x si y\n";
        std::cin>>x>>y;
        std::cout<<"Class\n";
        std::cin>>c;
        Bot* bot; //creez un jucator nou
        if (c==2){
            bot = new Mgunner(x, y);
            Data::getData().Team1()->push_back(bot);
        }
        else if (c==4){
            bot = new Sniper(x, y);
            Data::getData().Team1()->push_back(bot);
        }
        else if (c==3){
            bot = new Breacher(x, y);
            Data::getData().Team1()->push_back(bot);
        }
        else{
            bot = new Riflemen(x, y);
            Data::getData().Team1()->push_back(bot);
        }
        Data::getData().Pos()->push_back({Data::getData().Team1()->at(i)->pGetX(), Data::getData().Team1()->at(i)->pGetY()});
        AI ai(Data::getData().Team1()->at(i));
        team1.push_back(ai);
    }
    for(int i=0; i<8; i++){ //repeta pentru team2
        int x, y;
        x=i/4+1;
        y=i%4+1;
        Bot *bot;
        if (y==2){
            bot = new Mgunner(50-x, y);
            Data::getData().Team2()->push_back(bot);
        }
        else if (y==4){
            bot = new Sniper(50-x, y);
            Data::getData().Team2()->push_back(bot);
        }
        else if (y==3){
            bot = new Breacher(50-x, y);
            Data::getData().Team2()->push_back(bot);
        }
        else{
            bot = new Riflemen(50-x, y);
            Data::getData().Team2()->push_back(bot);
        }
        Data::getData().Pos()->push_back({Data::getData().Team2()->at(i)->pGetX(), Data::getData().Team2()->at(i)->pGetY()});
        AI ai(Data::getData().Team2()->at(i));
        team2.push_back(ai);
    }
    int rndCount=160; //nr de runde
    while(rndCount && team1.size() && team2.size()){ //treci prin runde
        std::cout<<"\n\nRound: "<<161-rndCount<<" "<<team1.size()<<"vs"<<team2.size()<<std::endl;
        for(int i=0; i<team1.size(); i++){ //executa mutarile primei echipe
            if(*(*Data::getData().Pos())[team1[i].getId()][0] != 101){ //daca este viu
                team1[i].think(); //actioneza
            }
            else{ //altfel
                team1.erase(team1.begin()+i); //sterge
                i--;
            }
        }
        for(int i=0; i<team2.size(); i++){ // la fel si pentru a doua echipa
            if(*(*Data::getData().Pos())[team2[i].getId()][0] != 101){
                team2[i].think();
            }
            else{
                team2.erase(team2.begin()+i);
                i--;
            }
        }
        for(int i=0; i<51; i++){ //printam terenul de lupta
            for(int j=0; j<51; j++){
                int x=0;
                for(auto k:team1){ //verificam daca este cineva din echipa 1 acolo
                    if(*Data::getData().Pos()->at(k.getId())[0]==i && *Data::getData().Pos()->at(k.getId())[1]==j){
                        std::cout<<"1 "; //printam
                        x=1;
                    }
                }
                for(auto k:team2){ //verificam daca este cineva din echipa 2 acolo
                    if(*Data::getData().Pos()->at(k.getId())[0]==i && *Data::getData().Pos()->at(k.getId())[1]==j){
                        std::cout<<"2 "; //printam
                        x=1;
                    }
                }
                if(!x){ //daca nu este nimeni
                    std::cout<<". "; // printam
                }
            }
            std::cout<<std::endl; //urmatorul rand
        }
        sleep_until(system_clock::now() + seconds(1)); //asteptam 1 sec
        rndCount--; //decrementam
    }
    if(team1.size() > team2.size()){ //afisam victoriosul
        std::cout<<"VICTORY!!!";
    }
    else if(team1.size() == team2.size()){
        std::cout<<"Drow";
    }
    else{
        std::cout<<"Defeat...";
    }
    std::cout<<"\n\nYour Team: "; // si aratam echipele
    for(auto &i:team1){
        i.getStats();
    }
    std::cout<<"\n\nThe Enemy Team: ";
    for(auto &i:team2){
        i.getStats();
    }
}