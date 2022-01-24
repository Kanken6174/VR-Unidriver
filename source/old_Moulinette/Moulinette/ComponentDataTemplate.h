#include <string>
using namespace std;
class ComponentDataTemplate {
public:
    int inputType = 99;        //0-5 pour choisir un vrai mode (analog, bool, skeleton...), 
                            //5+ pour le mode stub qui évalue l'update à partie de la touche de clavier correspondante
    string inputPath = "";    //Le chemin d'input SVR, exemple /input/a/click
    string valuePath = "";
};