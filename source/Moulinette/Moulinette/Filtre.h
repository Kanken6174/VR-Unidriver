#include<vector>

class Filtre
{
public:
	Filtre();
	~Filtre();
	vector<DriverDataTemplate*> ReadConfigAndBuildDrivers();
	void initClass(void);
	void split(const string& chaine, char delimiteur, vector& elements);
};
