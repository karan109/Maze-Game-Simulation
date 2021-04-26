#include "Health.hpp"
#include "Game.hpp"

Health::Health(SDL_Rect srcR_param, Entity * target_param) : Entity("../Images/dirt.png", srcR_param, srcR_param){
	target = target_param;
	int health = target->health;
	auto target_rect = target->getBB();
	destR.y = target_rect.y - 10;
	destR.x = target_rect.x;
	destR.w = target_rect.w * health / 100;
	destR.h = 5;
}

void Health::Update(){
	int health = target->health;
	auto target_rect = target->getBB();
	destR.y = target_rect.y - 10;
	destR.x = target_rect.x;
	destR.w = target_rect.w * health / 100;
	destR.h = 5;
}
void Health::Render(){
	int health = target->health;
	int c1 = health*255/100;
	SDL_SetRenderDrawColor(Game::renderer, 255-c1, c1, 0, 255); // the rect color (solid red)
	auto target_rect = target->getBB();
	SDL_RenderFillRect(Game::renderer, &destR);
}