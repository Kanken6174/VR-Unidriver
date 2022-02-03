#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


namespace serialport
{
	class Device {
	public:
		Device();
		void ReadConfigAndBuildDrivers(std::string file);



		struct Prop
		{
			std::string nom;
			std::string type;
			std::string flag;
			float valeur;
		};

		void affichageList();

		std::string nom;
		std::string port;
		int baudrate;
		std::list<Prop> listProp;
		float ping = 0;
	};
}