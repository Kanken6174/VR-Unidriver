#include <list>
#include <string>

using namespace std;

class Device {
public:
	Device();
	void ReadConfigAndBuildDrivers(string file);



	struct Prop
	{
		string nom;
		string type;
		string flag;
		float valeur;
	};

	void affichageList();

	string nom;
	string port;
	int baudrate;
	list<Prop> listProp;
	float ping = 0;
};
