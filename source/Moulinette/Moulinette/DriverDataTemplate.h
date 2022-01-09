#include <string>
#include "ComponentDataTemplate.h"
using namespace std;

class DriverDataTemplate {
public:
    string name = "default_name";    //le nom de l'appareil qui sera ajout�
    string renderModel = "";        //le mod�le 3d de l'appareil (optionnel)
    string serialNumber = "";        //le num�ro de s�rie (r�vision) de l'appareil
    int role = 0;    //d�faut � invalid (0), de 0 � 5 (1 main droite, 2 main gauche)
    vector<ComponentDataTemplate*> components;    //les divers composants du driver (boutons, joysticks, entr�es squelette...)
};