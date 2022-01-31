#include "VRDevice.h"

/// <summary>
/// Cette classe manage l'update des Devices et de leurs props
/// </summary>
class Manager{
private:
    list<VRDevice> devices;
public:
    Manager();
    void request(); //TODO code
    string to_string_devices(); //TODO code
};