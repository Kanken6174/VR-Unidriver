#include "VRComponent.h"
#include <string>

class VRButton : moulinette_components::VRComponent {
private:	
	bool pressed;
public:
	VRButton(bool press);
	~VRButton();

	bool isPressed();
	std::string to_string() override;
};

