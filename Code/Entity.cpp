#include "Game.hpp"
#include "Entity.hpp"
#include "Texture.hpp"

Entity::Entity(const char * texturesheet, int x, int y){
	objTexture = Texture::LoadTexture(texturesheet);
	xpos = x;
	ypos = y;
	xv = 0;
	yv = 0;
	srcR.h = height;
	srcR.w = width;
	srcR.x = 0;
	srcR.y = 0;
	// int speed = 3; 
}
void Entity::Update(){
	if(Game::event.type == SDL_KEYDOWN){
		auto key = Game::event.key.keysym.sym;
		if(key == SDLK_UP){
			yv = -1;
		}
		else if(key == SDLK_DOWN){
			yv = 1;
		}
		else if(key == SDLK_RIGHT){
			xv = 1;
		}
		else if(key == SDLK_LEFT){
			xv = -1;
		}
	}
	if(Game::event.type == SDL_KEYUP){
		auto key = Game::event.key.keysym.sym;
		if(key == SDLK_UP){
			yv = 0;
		}
		else if(key == SDLK_DOWN){
			yv = 0;
		}
		else if(key == SDLK_RIGHT){
			xv = 0;
		}
		else if(key == SDLK_LEFT){
			xv = 0;
		}
	}
	xpos += xv * speed;
	ypos += yv * speed;
	
	destR.x = xpos;
	destR.y = ypos;
	destR.w = srcR.w * scale;
	destR.h = srcR.h * scale;
}
void Entity::Render(){
	SDL_RenderCopy(Game::renderer, objTexture, & srcR, & destR);
}
Entity::~Entity(){
	SDL_DestroyTexture(objTexture);
}
