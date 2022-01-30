#include <string>
#include"VRComponent.h"
using namespace std;


class Trigger: public VRComponent { // potentiometre avec la valeure pour un doigts
private:
    double value;
public:
    double getValue();
    void setValue(int newValue);
    void calcValue(int Value);
};

//pour les valeur de 0 a 1
//#define DEBUG_MIN 0
//#define DEBUG_MAX 4095
