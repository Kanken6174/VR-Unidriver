#include <list>
#include <string>

using namespace std;

class Device {
public:
	Device();
	void ReadConfigAndBuildDrivers();

	

	struct Prop
	{
		string nom;
		string type;
		string flag;
	};

	string nom;
	string port;
	list<Prop> listProp;

};