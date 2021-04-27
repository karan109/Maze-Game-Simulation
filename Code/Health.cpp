#include "Health.hpp"
#include "Game.hpp"
#include "Texture.hpp"

Health::Health(SDL_Rect srcR_param, Entity * target_param, bool move_param) : Entity("../Images/dirt.png", srcR_param, srcR_param){
	target = target_param;
	white = Texture::LoadTexture("../Images/white.png");
	int health = target->health;
	auto target_rect = target->getBB();
	move = move_param;
	if(move == true){
		length = 50;
		destR.y = target_rect.y - 10;
		destR.x = target_rect.x + target_rect.w / 2 - length / 2;
		destR.w = length * health / full;
		destR.h = 5;
	}
	else{
		length = 150;
		destR.w = length * health / full;
		destR.h = 10;
		if(target->number == 1){
			destR.y = 20;
			destR.x = 30;
		}
		if(target->number  == 2){
			destR.y = 20;
			destR.x = Game::width - 30 - destR.w;
		}
		if(target->number  == 3){
			destR.y = 60;
			destR.x = Game::width - 30 - destR.w;
		}
		if(target->number  == 4){
			destR.y = 60;
			destR.x = Game::width - 30 - destR.w;
		}
	}
}

void Health::Update(){
	int health = target->health;
	if(move){
		auto target_rect = target->getBB();
		destR.y = target_rect.y - 10;
		destR.x = target_rect.x + target_rect.w / 2 - length / 2;
	}
	destR.w = length * health / full;
}
void Health::Render(){
	int health = target->health;
	int c1 = min((full - health) * 2 * 255 / full, 255);
	int c2 = min(health * 2 * 255 / full, 255);
	SDL_SetRenderDrawColor(Game::renderer, c1, c2, 0, 255);
	SDL_RenderFillRect(Game::renderer, &destR);
	int thick = 2;
	Texture::Draw(white, SDL_Rect{0, 0, 32, 32}, SDL_Rect{destR.x - thick, destR.y - thick, length + 2 * thick, thick});
	Texture::Draw(white, SDL_Rect{0, 0, 32, 32}, SDL_Rect{destR.x - thick, destR.y + destR.h, length + 2 * thick, thick});
	Texture::Draw(white, SDL_Rect{0, 0, 32, 32}, SDL_Rect{destR.x - thick, destR.y - thick, thick, destR.h + thick * 2});
	Texture::Draw(white, SDL_Rect{0, 0, 32, 32}, SDL_Rect{destR.x + length, destR.y - thick, thick, destR.h + thick * 2});
	Texture::Draw(white, SDL_Rect{0, 0, 32, 32}, SDL_Rect{destR.x + destR.w, destR.y, length - destR.w, destR.h});
	if(move) return;
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Game::font, (to_string(health) + " %").c_str(), SDL_Color{255, 255, 255, 255});
	SDL_Texture* Message = Texture::LoadTexture(surfaceMessage);

	SDL_Rect Message_rect;
	int digits = max((int)log10(health) + 1, 1) + 2;
	Message_rect.w = 15 * digits;
	Message_rect.h = 20;
	Message_rect.y = destR.y + destR.h / 2 - Message_rect.h / 2;
	if(target->number % 2 == 1) Message_rect.x = destR.x + length + thick + 10;
	else Message_rect.x = destR.x - thick - 10 - Message_rect.w;
	
	SDL_RenderCopy(Game::renderer, Message, NULL, & Message_rect);
}