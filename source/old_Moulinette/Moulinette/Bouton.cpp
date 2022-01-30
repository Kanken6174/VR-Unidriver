#include "Bouton.h"

bool Bouton::isPressed()
{
	if (this->value == 1) return true;
	else return false;
}
