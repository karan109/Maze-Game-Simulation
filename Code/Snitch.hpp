#pragma once

#include "Entity.hpp"
#include "Automated.hpp"

class Snitch : public Automated{
public:
	Snitch(SDL_Rect srcR_param, int start);
	void Update() override;

private:

};