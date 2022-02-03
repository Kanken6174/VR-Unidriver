#include "../SerialPort/serialPort.h"
#include "../SerialPort/Device.h"

#include "includes.h"
#include "componentHeaders.h"

using namespace serialport;

/// <summary>
/// Cette classe représente un Appareil et ses propriétés
/// </summary>
class VRDevice {
private:
    SerialPort* serialPort;
    vector<VRComponent*> components;
    VRQuaternion* internalRotation;
    float lastLatency;

public:
    VRDevice(vector<VRComponent*> components, SerialPort* serialPort);//TODO instance le VRDevice sans reponsabilité de lire le DMC
    virtual void updateValues();//TODO code
    virtual string to_string();//TODO code pour Preparer la trame pour le Driver
};