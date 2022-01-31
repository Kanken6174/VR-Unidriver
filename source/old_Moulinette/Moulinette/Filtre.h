#include<vector>
#include "Device.h"


class Filtre
{
private:
	Bouton button;
	Magneto mag;
	Accel acc;
	Gyro gyro;
	Trigger trigger;
	Joystick joyst;

public:
	Filtre();
	~Filtre();
	void initClass(list<Device::Prop> listProp);
	void split(const string& chaine, char delimiteur, vector& elements);
};