#include "Manage.h"
#include "Device.h"
#include "IPCServer.cpp"
#include "main.cpp"
#include "Filtre.h"
#include "Filtre.cpp"

#include <iostream>
#include <fstream>
#include <sstream>





using namespace std;


void Manage::requesteTrame() 
{
	int argumentCount = 0;
	const char* argumentValues{};

	main(argumentCount, argumentValues[]);

}
void Manage::envoieString(Quaternion quat, int delais, list<Bouton> lBouton, list<Trigger> lTrigger)
{
	Formater f =  Formater();
	f.FormaterDonnées(quat, delais, lBouton, lTrigger);

	this->moul.WriteToPipe(f->format, "\\\\.\\pipe\\driverPipe");

}

void Manage::manage()
{
	Filtre fil;
	Device periph;
	Manage::requesteTrame();
	fil.initClass(Device::listProp);


}

