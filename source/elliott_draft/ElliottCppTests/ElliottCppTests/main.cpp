#include "Log.h"
#include "Objet.h"

void testObjet() {
	Objet obj("Instance");
	Objet* pto = new Objet("Pointeur");
	obj.m();
	pto->m();

	obj.nom[0] = 'A';
	obj.m();

	pto->~Objet();
}

int main() {
	Log log; //default constructor is called; to give display level write log(Log::LevelInfo) (for example with info)
	log.Disp("Hello world! I am a log class.", Log::LevelInfo); //should not disp with default constructor
	log.Disp("This program is quite empty!", Log::LevelWarning); //should disp with default constructor
	testObjet();
	return 0;
}

