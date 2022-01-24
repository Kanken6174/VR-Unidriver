#pragma once
#include "Transformer.h"
#include <iostream>

class GloveTransformer : Transformer {
private:
	std::string format;
public:
	std::string transformeDonnees(float donnees, std::string type, std::string format) override;
	std::string toTransformIn(std::string format) override;
};