class Mapping
{
public:
	Mapping();
	~Mapping();
	vector<DriverDataTemplate*> ReadConfigAndBuildDrivers();
	void Mapping::initClass(void);
	void split(const string& chaine, char delimiteur, vector& elements);
};
