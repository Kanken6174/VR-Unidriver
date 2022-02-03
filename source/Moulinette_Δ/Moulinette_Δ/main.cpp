#include"VRAnalog.h"
#include"VRComponent.h"
#include"VRRelative.h"
#include "VRBoolean.h"
#include "VRQuaternion.h"

#include "ComponentReflector.h"	

#include<vector>
#include<iostream>

int main(int argc, char* argv[]) {
	VRAnalog* test = new VRAnalog();
	VRRelative* test2 = new VRRelative();
	vector<VRComponent*> composants = vector<VRComponent*>();
	composants.push_back(test);
	composants.push_back(test2);

	for (int i = 0; i < 10; i++) {
		for (VRComponent* component : composants) {
			component->receiveData(std::to_string(i * 24));
		}
	}

	for (VRComponent* component : composants) {
		ComponentReflector::provideDataToComponent(component, std::to_string(24*4));
	}

	for (VRComponent* component : composants) {
		std::cout << component->to_string();
	}
}