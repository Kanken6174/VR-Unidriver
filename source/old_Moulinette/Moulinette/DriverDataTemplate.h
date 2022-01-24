#include <string>
#include "ComponentDataTemplate.h"
using namespace std;

class DriverDataTemplate {
public:
    string name = "default_name";    //le nom de l'appareil qui sera ajouté
    string renderModel = "";        //le modèle 3d de l'appareil (optionnel)
    string serialNumber = "";        //le numéro de série (révision) de l'appareil
    int role = 0;    //défaut à invalid (0), de 0 à 5 (1 main droite, 2 main gauche)
    vector<ComponentDataTemplate*> components;    //les divers composants du driver (boutons, joysticks, entrées squelette...)
};