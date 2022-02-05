#include"VRAnalog.h"
#include"VRComponent.h"
#include"VRRelative.h"
#include "VRBoolean.h"
#include "VRQuaternion.h"
#include "VRDevice.h"

#include "ComponentReflector.h"	

#include<vector>
#include<iostream>


char* portName(string U) {
    char* src = new char[U.length() + 1];
    strcpy_s(src, U.length() + 1, U.c_str());
    return src;
}

int lectureDMC(vector<VRDevice*> *devices, string file ) {
    ifstream fichier(file, ios::in);

    if (fichier)
    {
        string ligne;
        while (getline(fichier, ligne))
        {
            char id = ligne[0];
            ligne = ligne.erase(0, 1);
            ligne.erase(remove(ligne.begin(), ligne.end(), '\n'), ligne.end()); //on enlve les \n parasites

            string nom;

            string port;
            int baudrate;

            vector<VRComponent*> composants = vector<VRComponent*>();

            switch (id)
            {
            case '$':   // Nom
                nom = ligne;
                break;
            case '&':   // Port COM
                port = ligne;
                break;
            case '!':   // baudrate a terminer
                baudrate = 74880;
                break;
            case '=':   // nouvel input = nouveau flag 

                getline(fichier, ligne);
                ligne = ligne.erase(0, 1);
                istringstream iss(ligne);
                int number;
                iss >> number;
                if (iss.fail()) {
                    cerr << "ERROR! conversion\n";
                    return 0;
                }

                string type;
                switch (number) {                           //Type du component a ajouté dans le vector
                case 0:
                    //"ABSOLUTE_T";
                {VRAnalog* component = new VRAnalog();
                getline(fichier, ligne);
                ligne = ligne.erase(0, 1);
                component->setFlag(ligne); }
                    break;
                case 1:
                    //"RELATIVE_T";
                {VRRelative* component = new VRRelative();
                getline(fichier, ligne);
                ligne = ligne.erase(0, 1);
                component->setFlag(ligne); }
                    break;
                case 2:
                    //"DIGITAL";
                {VRBoolean* component = new VRBoolean();
                getline(fichier, ligne);
                ligne = ligne.erase(0, 1);
                component->setFlag(ligne); }
                    break;
                case 3:
                    //"HAPTIC"
                    break;
                case 4:
                    //"SKELETAL"
                    break;
                case 5:
                    //"RESERVED"
                    break;
                case 6:
                    //"QUATERNIONS"
                    break;
                default:
                    //"DEFAULT"
                    break;
                }

                SerialPort w;


                VRDevice* device = new VRDevice(nom,composants,&w);
                devices->push_back(device);
                break;
            }
        }
        return 1;
    }
    else {
        cerr << "Erreur lecture fichier DMC" << endl;
        return 0;
    }
}

int main(int argc, char* argv[]) {

    vector<VRDevice*> devices = vector<VRDevice*>();

    lectureDMC(&devices, "gant.dmc");


    /*
    VRAnalog* test = new VRAnalog();
    test->setFlag("A");
    VRRelative* test2 = new VRRelative();
    vector<VRComponent*> composants = vector<VRComponent*>();
    composants.push_back(test);
    composants.push_back(test2);

    SerialPort w;
    VRDevice* device = new VRDevice("test", composants, &w);


    for (int i = 0; i < 10; i++) {
        for (VRComponent* component : composants) {
            component->receiveData(std::to_string(i * 24));
        }
    }

    for (VRComponent* component : composants) {
        ComponentReflector::provideDataToComponent(component, std::to_string(24*4));
    }

    for (VRComponent* component : composants) {
        std::cout << component->to_string() << endl;
        std::cout << component->getFlag() << endl;
    }
    */
}

