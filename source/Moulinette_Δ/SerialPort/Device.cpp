#include "Device.h"

namespace serialport
{
    Device::Device() {}

    void Device::ReadConfigAndBuildDrivers(std::string file) {
        std::ifstream fichier(file, std::ios::in);

        if (fichier)
        {
            std::string ligne;
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
                    std::istringstream iss(ligne);
                    int number;
                    iss >> number;
                    if (iss.fail()) {
                        std::cerr << "ERROR!\n";
                        return;
                    }

                    std::string type;
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
            std::cerr << "Erreur lecture fichier" << std::endl;
        }

    }

    void Device::affichageList() {
        std::list<Device::Prop>::iterator it;
        it = this->listProp.begin();
        while (it != this->listProp.end()) {
            std::cout << "Valeur: " << it->valeur << " Flag: " << it->flag << std::endl;
            it++;
        }
        std::cout << "Ping : " << this->ping << std::endl;
    }

}