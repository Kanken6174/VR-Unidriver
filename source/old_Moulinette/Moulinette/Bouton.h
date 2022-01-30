#include <string>
#include"VRComponent.h"
using namespace std;

class Bouton: public VRComponent { // button avec sa valeure
private:
    double value;

public:
    bool isPressed();
};



