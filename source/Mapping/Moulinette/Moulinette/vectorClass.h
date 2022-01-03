class ComponentDataTemplate {
public:
    int inputType = 99;        //0-5 pour choisir un vrai mode (analog, bool, skeleton...), 
                            //5+ pour le mode stub qui �value l'update � partie de la touche de clavier correspondante
    string inputPath = "";    //Le chemin d'input SVR, exemple /input/a/click
    string valuePath = "";
};


class DriverDataTemplate {
public:
    string name = "default_name";    //le nom de l'appareil qui sera ajout�
    string renderModel = "";        //le mod�le 3d de l'appareil (optionnel)
    string serialNumber = "";        //le num�ro de s�rie (r�vision) de l'appareil
    int role = TrackedControllerRole_Invalid;    //d�faut � invalid (0), de 0 � 5 (1 main droite, 2 main gauche)
    vector<ComponentDataTemplate*> components;    //les divers composants du driver (boutons, joysticks, entr�es squelette...)
};

//Classe permetant la d�conposition de inputPath
class Element {
public:
    string index = "";
    string name = "";
    string pos = "";
};

//class repr�sentant les differrents composants
class Magneto { // magn�tom�tre avec les valeures x/y/z
public:
    int posX;
    char indexX;
    double valX;

    int posY;
    char indexY;
    double valY;

    int posZ;
    char indexZ;
    double valZ;
}

class Gyro { // gyrom�tre avec les valeures x/y/z
public:
    int posX;
    char indexX;
    double valX;

    int posY;
    char indexY;
    double valY;

    int posZ;
    char indexZ;
    double valY;
}

class Accel { // accel�rom�tre avec les valeures x/y/z
public:
    int posX;
    char indexX;
    double valX;

    int posY;
    char indexY;
    double valY;

    int posZ;
    char indexZ;
    double valY;
}

class AllTrigger {
public:
    vector<Trigger*> components; // gachette ou potentiometre
};

class Trigger { // potentiometre avec la valeure pour un doigts
public:
    string name = "";
    int pos = 99;
    char index = "";
    double thumbXVal = 99;
}

class AllBouton {
public:
    vector<Bouton*> components; // Les diverts boutons
};

class Bouton { // button avec sa valeure
public:
    int pos = 99;
    char index = "";
    bool valeur = 99;
};

class AllJoystick {
public:
    vector<Trigger*> components; // Les diverts joysticks
};

class Joystick { // joystique avec sa valeure
public:
    int pos = 99;
    char index = "";
    double valeur = 99;
};

//pour les valeur de 0 a 1
//#define DEBUG_MIN 0
//#define DEBUG_MAX 4095

//if (value < valueMin && value != DEBUG_MIN)
//    valueMin = value;
//if (value > valueMax && value != DEBUG_MIN)
//    valueMax = value;

//value -= valueMin;

//value /= valueMax;

//////////////////////////////////////////////////////////////////////////:

//pour les valeur de -1 a 1
//#define DEBUG_MIN 0
//#define DEBUG_MAX 4095

//if (value < valueMin && value != DEBUG_MIN)
//    valueMin = value;
//if (value > valueMax && value != DEBUG_MIN)
//    valueMax = value;

//value -= (valueMax/2);
//valueMin -= (valueMax/2);
//valueMax /= 2; 

//value -= valueMin;

//value /= valueMax;