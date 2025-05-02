#ifndef glbFread
#define glbFread
#include <fstream>
#include <string>

class Fread
{
private:
    static std::ifstream fin;
public:
    static void fOpen(std::string fName){
        fin.open(fName);
    }
    static void fClose(){
        fin.close();
    }
    template <typename T>
    static void fRead(T &t){
        fin>>t;
    }
};

inline std::ifstream Fread::fin;

#endif