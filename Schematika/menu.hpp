#pragma once
#include "sl.h"
#include "string"


struct Menu
{
	std::string name;
	double x = 0, y = 0;
	double width = 0, height = 0;
	bool isClicked = false;
};
