#include "Game.hpp"
#include "Texture.hpp"

SDL_Texture * Texture::LoadTexture(const char * texture){
	SDL_Surface * tempSurface = IMG_Load(texture);
	SDL_Texture * tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}
SDL_Texture * Texture::LoadTexture(SDL_Surface * tempSurface){
	SDL_Texture * tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}
void Texture::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest){
	SDL_RenderCopy(Game::renderer, tex, & src, & dest);
}