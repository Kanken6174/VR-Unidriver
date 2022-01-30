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

void Filtre::initClass(list<Device::Prop> listProp)
{
    int i = 0;
    Device::Prop chaine;
    vector<Element*> element = vector<Element*>();

    while (listProp.size() != i)
    {
        switch (listProp) // input,pos,hand
        {
        case 'input/click/':
            this->button->bout->pos = listProp->Prop; //Type a véridier
            this->button->bout->val = listProp->valeur;
            listprop.next();
            break;
        case '': //pour gachette
            this->trigger->trig->pos = listProp->type; //Type a véridier
            this->trigger->trig->val = listProp->valeur;
            listprop++;
            break;
        case '': //pour joystick
            this->joyst->joystick->pos = listProp->type; //Type a véridier
            this->joyst->joystick->val = listProp->valeur;
            this->joyst++;
            listprop++;
            break;
        case '/pose/mag/x':
            this->mag->X->pos = listProp->type; //Type a véridier
            this->mag->X->val = listProp->valeur;
            listprop++;
            break;
         case '/pose/mag/y':
             this->mag->Y->pos = listProp->type; //Type a véridier
             this->mag->Y->val = listProp->valeur;
             listprop++;
             break;
        case '/pose/mag/z':
            this->mag->Z->pos = listProp->type; //Type a véridier
            this->mag->Z->val = listProp->valeur;
            listprop++;
            break;
        case '/pose/acc/x':
            this->acc->X->pos = listProp->type; //Type a véridier
            this->acc->X->val = listProp->valeur;
            listprop++;
            break;
        case '/pose/acc/y':
            this->acc->Y->pos = listProp->type; //Type a véridier
            this->acc->Y->val = listProp->valeur;
            listprop++;
            break;
        case '/pose/acc/z':
            this->acc->Z->pos = listProp->type; //Type a véridier
            this->acc->Z->val = listProp->valeur;
            listprop++;
            break;
        case '/pose/gyro/x':
            this->gyro->X->pos = listProp->type; //Type a véridier
            this->gyro->X->val = listProp->valeur;
            listprop++;
            break;
        case '/pose/gyro/y':
            this->gyro->Y->pos = listProp->type; //Type a véridier
            this->gyro->Y->val = listProp->valeur;
            listprop++;
            break;
        case '/pose/gyro/z':
            this->gyro->Z->pos = listProp->type; //Type a véridier
            this->gyro->Z->val = listProp->valeur;
            listprop++;
            break;
        case 'hand':
            this->trigger->trig->pos = listProp->type; //Type a véridier
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
