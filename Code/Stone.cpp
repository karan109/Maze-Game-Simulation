#include "Stone.hpp"
#include "Game.hpp"
#include "Texture.hpp"
#include "Collision.hpp"
Stone::Stone(const char * texturesheet, SDL_Rect srcR_param, int start, int height_param, int width_param) : Entity(texturesheet, srcR_param, start){
	auto coords = getAutoBlockCoords(start);
	destR.x = coords.second + Game::block_w / 2 - width_param / 2;
	destR.y = coords.first + Game::block_h / 2 - height_param / 2;
	destR.w = width_param;
	destR.h = height_param;
	xpos = destR.x;
	ypos = destR.y;
	xv = 0;
	yv = 0;
}
void Stone::Update(){
	auto drone = (*(Game::entities->drones))[0];
	int dir = Collision::AABB(getBB(), drone->getBB(), getXV(), getYV(), drone->getXV(), drone->getYV());
	if(dir != 0){
		Mix_PlayChannel( -1, Game::gHigh, 0 );
		Game::entities->Delete(this);
	}
}