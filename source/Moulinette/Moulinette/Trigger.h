#include <string>
using namespace std;


class Trigger { // potentiometre avec la valeure pour un doigts
public:
    string name = "";
    int pos = 99;
    char index = "";
    double thumbXVal = 99;
};

//class AllTrigger {
//public:
//    vector<Trigger*> components; // gachette ou potentiometre
//};





//pour les valeur de 0 a 1
//#define DEBUG_MIN 0
//#define DEBUG_MAX 4095


// filtre 
//if (value < valueMin && value != DEBUG_MIN)
//    valueMin = value;
//if (value > valueMax && value != DEBUG_MIN)
//    valueMax = value;

//value -= valueMin;

//value /= valueMax;