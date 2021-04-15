#include "Game.hpp"
#include "Entity.hpp"
#include "Texture.hpp"

Entity::Entity(const char * texturesheet, SDL_Rect srcR_param, SDL_Rect destR_param){
	objTexture = Texture::LoadTexture(texturesheet);
	srcR = srcR_param;
	destR = destR_param;
	xpos = destR.x;
	ypos = destR.y;
	xv = 0;
	yv = 0;
}
void Entity::Update(){
	
}
void Entity::Render(){
	SDL_RenderCopy(Game::renderer, objTexture, & srcR, & destR);
}
Entity::~Entity(){
	SDL_DestroyTexture(objTexture);
}
int Entity::getX(){
	return xpos;
}
int Entity::getY(){
	return ypos;
}
void Entity::setX(int x){
	xpos = x;
}
void Entity::setY(int y){
	ypos = y;
}
int Entity::getXV(){
	return xv;
}
int Entity::getYV(){
	return yv;
}
void Entity::setXV(int xv_param){
	xv = xv_param;
}
void Entity::setYV(int yv_param){
	yv = yv_param;
}
SDL_Rect Entity::getBB(){
	return destR;
}
