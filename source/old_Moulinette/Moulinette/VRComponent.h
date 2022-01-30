#include <string>
using namespace std;

class VRComponent
{
private:
	int pos;

public:
	VRComponent();
	~VRComponent();

	int getPos();
	string to_string();

};
