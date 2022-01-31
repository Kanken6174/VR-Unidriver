#include "../SerialPort/serialPort.h"
#include "../SerialPort/Device.h"
#include "includes.h"
#include "VRComponent.h"
#include <list>

using namespace serialport;

/// <summary>
/// Cette classe représente un Appareil et ses propriétés
/// </summary>
class VRDevice {
private:
    SerialPort serialPort;
    list<VRComponent> components;
    float lastLatence;

public:
    VRDevice(list<VRComponent>, SerialPort);//TODO instance le VRDevice sans reponsabilité de lire le DMC
    void updateValues();//TODO code
    string to_string();//TODO code pour Preparer la trame pour le Driver
};