#include "Filtre.h"
#include "Bouton.h"
#include "Accel.h"
#include "ComponentDataTemplate.h"
#include "DriverDataTemplate.h"
#include "Joystick.h"
#include "Element.h"
#include "Gyro.h"
#include "Magneto.h"
#include "Trigger.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <WinSock2.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Filtre::Filtre()
{

}

Filtre::~Filtre()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Filtre::initClass(void)
{
    int i = 0;
    vector<DriverDataTemplate*> DriverTemplates = vector<DriverDataTemplate*>();
    vector<AllTrigger*> trigg = vector<AllTrigger*>();
    vector<AllBouton*> bout = vector<AllBouton*>();
    vector<AllJoystick*> joy = vector<AllJoystick*>();
    string chaine = "";
    vector<Element*> element = vector<Element*>();
    DriverTemplates = ReadConfig();

    while (DriverTemplates[i] != NULL)
    {
        // si c'est bien un composant

        chaine = DriverTemplates->components->inputPath;
        element = split(chaine, delimiteur, elements);
        switch (element[1]) // input,pos,hand
        {
        case 'input':
            switch element[3]
            {
            case 'clisk':
                button = new Bouton;
                bout->components.push_back(button);
                bout->components->pos = DriverTemplates[i]->components->inputType;
                bout->components->index = DriverTemplates[i]->components->valuePath;
            case '': //pour gachette
                trigger = new Trigger;
                trigg->components.push_back(trigger);
                trigg->components->name = element[3];
                trigg->components->pos = DriverTemplates[i]->components->inputType;
                trigg->components->index = DriverTemplates[i]->components->valuePath;
            case '': //pour joystick
                joyst = new Joystick;
                joy->components.push_back(trigger);
                joy->components->pos = DriverTemplates[i]->components->inputType;
                joy->components->index = DriverTemplates[i]->components->valuePath;
            default:
                break;
            }
        case 'pose':
            switch element[2]
            {
            case 'mag':
                mag = new Magneto;
                switch (element[3])
                {
                case 'x':
                    mag->posX = DriverTemplates[i]->components->inputType;
                    mag->indexX = DriverTemplates[i]->components->valuePath;
                    break;
                case 'y':
                    mag->posY = DriverTemplates[i]->components->inputType;
                    mag->indexY = DriverTemplates[i]->components->valuePath;
                    break;
                case 'z':
                    mag->posZ = DriverTemplates[i]->components->inputType;
                    mag->indexZ = DriverTemplates[i]->components->valuePath;
                    break;
                default:
                    break;
                }
            case 'acc':
                acc = new Accel;
                switch (element[3])
                {
                case 'x':
                    acc->posX = DriverTemplates[i]->components->inputType;
                    acc->indexX = DriverTemplates[i]->components->valuePath;
                    break;
                case 'y':
                    acc->posY = DriverTemplates[i]->components->inputType;
                    acc->indexY = DriverTemplates[i]->components->valuePath;
                    break;
                case 'z':
                    acc->posZ = DriverTemplates[i]->components->inputType;
                    acc->indexZ = DriverTemplates[i]->components->valuePath;
                    break;
                default:
                    break;
                }
            case 'gyro':
                gyro = new Gyro;
                switch (element[3])
                {
                case 'x':
                    gyro->posX = DriverTemplates[i]->components->inputType;
                    gyro->indexX = DriverTemplates[i]->components->valuePath;
                    break;
                case 'y':
                    gyro->posY = DriverTemplates[i]->components->inputType;
                    gyro->indexY = DriverTemplates[i]->components->valuePath;
                    break;
                case 'z':
                    gyro->posZ = DriverTemplates[i]->components->inputType;
                    gyro->indexZ = DriverTemplates[i]->components->valuePath;
                    break;
                default:
                    break;
                }
            }
        case 'hand':
            trigger = new Trigger;
            trigg->components.push_back(trigger);
            trigg->components->name = element[3];
            trigg->components->pos = DriverTemplates[i]->components->inputType;
            trigg->components->index = DriverTemplates[i]->components->valuePath;
            break;
        default:
            break;
        }
        i++;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void split(const string chaine, char delimiteur, vector<Element*> elements)
{
    stringstream ss(chaine);
    string sousChaine;
    while (getline(ss, sousChaine, delimiteur))
    {
        for (int i = 0; i < 3; ++i) {
            if (i == 0)
                element->index = sousChaine;
            if (i == 1)
                element->name = sousChaine;
            else
                element->pos = sousChaine;
        }
    }
}