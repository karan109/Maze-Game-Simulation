#pragma once

#include "Entity.hpp"
#include "Automated.hpp"

class Snitch : public Automated{
public:
	int disapparation_time = 10;
	Snitch(SDL_Rect srcR_param, int start);
	void Update();

private:

};