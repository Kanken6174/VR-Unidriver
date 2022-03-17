#include "../SerialPort/serialPort.h"

#include "componentHeaders.h"	


using namespace serialport;

/// <summary>
/// Cette classe représente un Appareil et ses propriétés
/// </summary>
class VRDevice {
private:
    SerialPort* serialPort;
    vector<unique_ptr<VRComponent>> components;
    unique_ptr<VRQuaternion> internalRotation;
    float lastLatency;
    string nom;
    unsigned compteur = 0;

public:
    VRDevice();
    VRDevice(string nom, vector<unique_ptr<VRComponent>> components, SerialPort* serialPort);
    virtual string getName();
    virtual void setName(string name);
    virtual void setSerialport(SerialPort* serial);
    virtual void addComponents(unique_ptr<VRComponent> components);
    virtual void updateValues();
    string requestTram();
    virtual string to_string();
};