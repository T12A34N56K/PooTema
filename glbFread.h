#ifndef glbFread
#define glbFread
#include <fstream>
#include <string>

class Fread // wrapper pentru ifstream
{
private:
    static std::ifstream fin; // variabila de baza
public:
    static void fOpen(std::string fName){ // deschiderea unui nou fisier
        fin.open(fName);
    }
    static void fClose(){ // inchidere
        fin.close();
    }
    template <typename T> // citire cu template
    static void fRead(T &t){
        fin>>t;
    }
};

inline std::ifstream Fread::fin;

#endif