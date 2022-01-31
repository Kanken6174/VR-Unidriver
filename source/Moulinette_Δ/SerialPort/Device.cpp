#include "Device.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


namespace serialport
{
    Device::Device() {}

    void Device::ReadConfigAndBuildDrivers(string file) {
        ifstream fichier(file, ios::in);

        if (fichier)
        {
            string ligne;
            while (getline(fichier, ligne))
            {
                char id = ligne[0];
                ligne = ligne.erase(0, 1);
                ligne.erase(remove(ligne.begin(), ligne.end(), '\n'), ligne.end()); //on enlve les \n parasites


                switch (id)
                {
                case '$':   // Nom
                    this->nom = ligne;
                    break;
                case '&':   // Port COM
                    this->port = ligne;
                    break;
                case '!':   // baudrate a terminer
                    this->baudrate = 74880;
                    break;
                case '=':   // nouvel input = nouveau flag 

                    Prop p;
                    p.nom = ligne;

                    getline(fichier, ligne);
                    ligne = ligne.erase(0, 1);
                    istringstream iss(ligne);
                    int number;
                    iss >> number;
                    if (iss.fail()) {
                        cerr << "ERROR!\n";
                        return;
                    }

                    string type;
                    switch (number) {
                    case 0:
                        type = "ABSOLUTE_T";
                        break;
                    case 1:
                        type = "RELATIVE_T";
                        break;
                    case 2:
                        type = "DIGITAL";
                        break;
                    case 3:
                        type = "HAPTIC";
                        break;
                    case 4:
                        type = "SKELETAL";
                        break;
                    case 5:
                        type = "RESERVED";
                        break;
                    case 6:
                        type = "QUATERNIONS";
                        break;
                    default:
                        type = "DEFAULT";
                        break;
                    }
                    p.type = type;


                    getline(fichier, ligne);
                    ligne = ligne.erase(0, 1);
                    p.flag = ligne;

                    this->listProp.push_back(p);
                    break;
                }
            }
        }
        else {
            cerr << "Erreur lecture fichier" << endl;
        }

    }

    void Device::affichageList() {
        list<Device::Prop>::iterator it;
        it = this->listProp.begin();
        while (it != this->listProp.end()) {
            cout << "Valeur: " << it->valeur << " Flag: " << it->flag << endl;
            it++;
        }
        cout << "Ping : " << this->ping << endl;
    }

}