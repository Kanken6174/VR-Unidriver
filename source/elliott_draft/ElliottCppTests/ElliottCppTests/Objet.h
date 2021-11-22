#pragma once
#include "Log.h"
#include <iostream>
#include <string>
class Objet
{
public:
	Objet(std::string nom) : nom(nom), log(Log::LevelInfo)
	{}

	void m() {
		std::string msg = "Mon nom est " + nom;
		log.Disp(msg, Log::LevelInfo);
	}

	std::string nom;
private:
	Log log;
};

