#include<vector>
#include"Device.h"

class Filtre
{
private:
	button = new Bouton;
	mag = new Magneto;
	acc = new Accel;
	gyro = new Gyro;
	trigger = new Trigger;
	joyst = new Joystick;

public:
	Filtre();
	~Filtre();
	void initClass(list<Prop> listProp);
	void split(const string& chaine, char delimiteur, vector& elements);
};
