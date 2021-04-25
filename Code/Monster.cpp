#include "Monster.hpp"
#include "Game.hpp"
#include "Collision.hpp"


Monster::Monster(SDL_Rect srcR_param, int start) : Automated("../Images/pacman.png", srcR_param, start){
	speed = 2.5;
	target = nullptr;
}

void Monster::Update() {
	Automated::Update();
}