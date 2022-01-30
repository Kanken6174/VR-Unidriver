#include "Device.h"
#include "serialPort.h"
#include "IPCServer.h"
#include "Formater.h"

class Manage {
public:

	PipeServer moul = PipeServer("\\\\.\\pipe\\moulinette");	
	
	void requesteTrame();
	void envoieString(Quaternion quat, int delais, list<Bouton> lBouton, list<Trigger> lTrigger);
	void manage();

};