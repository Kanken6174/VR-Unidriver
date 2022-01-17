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
#include "Device.h"
#include "StructData.h"

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

void Filtre::initClass(list<Prop> listProp)
{
    int i = 0;
    string chaine = "";
    vector<Element*> element = vector<Element*>();

    while (listProp != NULL)
    {
        // si c'est bien un composant

        chaine = listProp->nom;
        element = split(chaine, '|', element);
        switch (element[1]) // input,pos,hand
        {
        case 'input':
            switch element[3]
            {
            case 'click':
                
                this.button->bout->name = listProp->name;
                this.button->bout->pos = listProp->type; //Type a véridier
                this.button->bout->index = listProp->flag;
                this.button->bout->val = listProp->valeur;
                this.button++;
                listprop++;
                break;
            case '': //pour gachette
               
                this->trigger->trig->name = listProp->name;
                this->trigger->trig->pos = listProp->type; //Type a véridier
                this->trigger->trig->index = listProp->flag;
                this->trigger->trig->val = listProp->valeur;
                this->trigger++;
                listprop++;
                break;
            case '': //pour joystick
                
                this->joyst->joystick->name = listProp->name;
                this->joyst->joystick->pos = listProp->type; //Type a véridier
                this->joyst->joystick->index = listProp->flag;
                this->joyst->joystick->val = listProp->valeur;
                this->joyst++;
                listprop++;
                break;
            default:
                break;
            }
        case 'pose':
            switch (element[2])
            {
            case 'mag':
                
                switch (element[3])
                {
                case 'x':
                    this->mag->X->name = listProp->name;
                    this->mag->X->pos = listProp->type; //Type a véridier
                    this->mag->X->index = listProp->flag;
                    this->mag->X->val = listProp->valeur;
                    listprop++;
                    break;
                case 'y':
                    this->mag->Y->name = listProp->name;
                    this->mag->Y->pos = listProp->type; //Type a véridier
                    this->mag->Y->index = listProp->flag;
                    this->mag->Y->val = listProp->valeur;
                    listprop++;
                    break;
                case 'z':
                    this->mag->Z->name = listProp->name;
                    this->mag->Z->pos = listProp->type; //Type a véridier
                    this->mag->Z->index = listProp->flag;
                    this->mag->Z->val = listProp->valeur;
                    listprop++;
                    break;
                default:
                    break;
                }
            case 'acc':
                
                switch (element[3])
                {
                case 'x':
                    this->acc->X->name = listProp->name;
                    this->acc->X->pos = listProp->type; //Type a véridier
                    this->acc->X->index = listProp->flag;
                    this->acc->X->val = listProp->valeur;
                    listprop++;
                    break;
                case 'y':
                    this->acc->Y->name = listProp->name;
                    this->acc->Y->pos = listProp->type; //Type a véridier
                    this->acc->Y->index = listProp->flag;
                    this->acc->Y->val = listProp->valeur;
                    listprop++;
                    break;
                case 'z':
                    this->acc->Z->name = listProp->name;
                    this->acc->Z->pos = listProp->type; //Type a véridier
                    this->acc->Z->index = listProp->flag;
                    this->acc->Z->val = listProp->valeur;
                    listprop++;
                    break;
                default:
                    break;
                }
            case 'gyro':
                
                switch (element[3])
                {
                case 'x':
                    this->gyro->X->name = listProp->name;
                    this->gyro->X->pos = listProp->type; //Type a véridier
                    this->gyro->X->index = listProp->flag;
                    this->gyro->X->val = listProp->valeur;
                    listprop++;
                    break;
                case 'y':
                    this->gyro->Y->name = listProp->name;
                    this->gyro->Y->pos = listProp->type; //Type a véridier
                    this->gyro->Y->index = listProp->flag;
                    this->gyro->Y->val = listProp->valeur;
                    listprop++;
                    break;
                case 'z':
                    this->gyro->Z->name = listProp->name;
                    this->gyro->Z->pos = listProp->type; //Type a véridier
                    this->gyro->Z->index = listProp->flag;
                    this->gyro->Z->val = listProp->valeur;
                    listprop++;
                    break;
                default:
                    break;
                }
            }
        case 'hand':
            
            this->trigger->trig->name = listProp->name;
            this->trigger->trig->pos = listProp->type; //Type a véridier
            this->trigger->trig->index = listProp->flag;
            this->trigger->trig->val = listProp->valeur;
            this->trigger++;
            listprop++;
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