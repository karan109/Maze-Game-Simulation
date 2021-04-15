#include "Wall.hpp"
#include "Game.hpp"

Wall::Wall(SDL_Rect srcR_param, SDL_Rect destR_param) : Entity("../Images/grass.png", srcR_param, destR_param){
}

void Wall::Update(){
	cout<<"ok";
}