#include "Monster.hpp"
#include "Game.hpp"
#include "Collision.hpp"

Snitch::Snitch(SDL_Rect srcR_param, int start) : Automated("../Images/snitch.png", srcR_param, start){
	speed = 2.5;
}

void Snitch::Update(){}