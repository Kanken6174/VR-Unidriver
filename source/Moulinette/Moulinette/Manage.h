#include "Device.h"
#include "serialPort.h"
#include "IPCServer.h"
#include "Formater.h"

class Manage {
public:

	PipeServer moul = PipeServer("\\\\.\\pipe\\moulinette");
	

	void requestTrame(SerialPort w, Device periph) {};
		
	void envoieString(Quaternion quat, int delais, list<Bouton> lBouton, list<Trigger> lTrigger);

};