#include <string>
#include "Bouton.h"
#include "Trigger.h"



class Formater {
public:
	std::string format;

	Formater();
	~Formater();

	void FormaterDonnées(Quaternion quat, int delais, list<Bouton> lBouton, list<Trigger> lTrigger );
	string to_stringQuat(Quaternion q);
	

};