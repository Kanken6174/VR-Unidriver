#include "../SerialPort/serialPort.h"
#include "../SerialPort/Device.h"

#include "ComponentReflector.h"	

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
    string nom;

public:
    VRDevice();
    VRDevice(string nom, vector<VRComponent*> components, SerialPort* serialPort);
    virtual string getName();
    virtual void setName(string name);
    virtual void setSerialport(SerialPort* serial);
    virtual void addComponents(VRComponent* components);
    virtual void updateValues();
    string requestTram();
    virtual string to_string();//TODO code pour Preparer la trame pour le Driver
};