#pragma once

#include "Entity.hpp"
#include "Automated.hpp"

class Drone : public Automated{
public:
	Drone(SDL_Rect srcR_param, int start);
	void Update();
private:
};