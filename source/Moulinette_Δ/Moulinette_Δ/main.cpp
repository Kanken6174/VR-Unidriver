#include"VRAnalog.h"
#include"VRComponent.h"
#include<vector>

#define BUTTON 2;
#define ANALOG 1;

int main(int argc, char* argv[]) {
	//TODO code
	VRAnalog test = VRAnalog();
	vector<VRComponent> composants = vector<VRComponent>();
	composants.push_back(test);
	switch (composants[0].gettype()) {
	case 3:
		break;
	default:
		break;
	}
}