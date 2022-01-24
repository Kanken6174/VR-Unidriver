#pragma once

#include <iostream>

class Utilisable {
public:
	virtual void utilise() = 0;
private:
	int position;
	std::string touche;
	int val;
};