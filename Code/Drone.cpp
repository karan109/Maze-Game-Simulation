#include "Drone.hpp"
#include "Game.hpp"
#include "Collision.hpp"

// Inherites from Automated class
Drone::Drone(SDL_Rect srcR_param, int start) : Automated("../Images/drone2.png", srcR_param, start){
	speed = 4;
	// Set speed of drone

	set_mode(4);

}
// Update function
void Drone::Update(){
	Entity::Update();
}