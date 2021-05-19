#include "Health.hpp"
#include "Game.hpp"
#include "Texture.hpp"

Health::Health(SDL_Rect srcR_param, Entity * target_param, bool move_param, bool show_param) : Entity("../Images/dirt.png", srcR_param, srcR_param){
	target = target_param;
	white = Texture::LoadTexture("../Images/white.png");
	black = Texture::LoadTexture("../Images/black.png");
	snitch = Texture::LoadTexture("../Images/snitch.png");
	broom = Texture::LoadTexture("../Images/broom.png");
	cloak = Texture::LoadTexture("../Images/cloak_black.png");
	int health = target->health;
	auto target_rect = target->getBB();
	move = move_param;
	show = show_param;
	figure.w = 32;
	figure.h = 32;

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
			destR.x = 50;
		}
		if(target->number  == 2){
			destR.y = 20;
			destR.x = Game::width - 50 - destR.w;
		}
		if(target->number  == 3){
			destR.y = 100;
			destR.x = 50;
		}
		if(target->number  == 4){
			destR.y = 100;
			destR.x = Game::width - 50 - destR.w;
		}
	}
	figure.y = destR.y + destR.h / 2 - figure.h / 2;
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
	if(!show) return;
	int health = target->health;
	int c1 = min((full - health) * 2 * 255 / full, 255);
	int c2 = min(health * 2 * 255 / full, 255);
	SDL_SetRenderDrawColor(Game::renderer, c1, c2, 0, 255);
	SDL_RenderFillRect(Game::renderer, &destR);
	int thick = 2;
	auto color = white;
	// if(! move) color = black;
	Texture::Draw(color, SDL_Rect{0, 0, 32, 32}, SDL_Rect{destR.x - thick, destR.y - thick, length + 2 * thick, thick});
	Texture::Draw(color, SDL_Rect{0, 0, 32, 32}, SDL_Rect{destR.x - thick, destR.y + destR.h, length + 2 * thick, thick});
	Texture::Draw(color, SDL_Rect{0, 0, 32, 32}, SDL_Rect{destR.x - thick, destR.y - thick, thick, destR.h + thick * 2});
	Texture::Draw(color, SDL_Rect{0, 0, 32, 32}, SDL_Rect{destR.x + length, destR.y - thick, thick, destR.h + thick * 2});
	Texture::Draw(color, SDL_Rect{0, 0, 32, 32}, SDL_Rect{destR.x + destR.w, destR.y, length - destR.w, destR.h});
	if(move) return;
	SDL_Rect fig = target->srcR;
	if(target->number % 2 == 1){
		figure.x = 9;
	}
	else{
		figure.x = Game::width - 9 - 32;
	}
	if(target->number<3){
		fig.y = 4 * 32;
		fig.x = 0;
	}
	else{
		fig.y = 2 * 161;
		fig.x = 0;
	}
	string temp = Game::player_name;
	if(target->number == 1 or target->number == 2){
		if(target->number == 2) temp = Game::remote_name;
		if(temp == "harry1") temp = "Harry";
		if(temp == "ron") temp = "Ron";
		if(temp == "hermione") temp = "Hermione";
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Game::font, (temp).c_str(), SDL_Color{255, 255, 255, 255});
		SDL_Texture* Message = Texture::LoadTexture(surfaceMessage);
		SDL_Rect Message_rect;
		int digits = temp.size();
		Message_rect.w = 15 * digits;
		Message_rect.h = 20;
		Message_rect.y = destR.y + 5 + destR.h;
		Message_rect.x = destR.x + length / 2 - Message_rect.w / 2;
		SDL_RenderCopy(Game::renderer, Message, NULL, & Message_rect);
		SDL_Rect l;
		l.y = Message_rect.y;
		l.w = 20;
		l.h = 20;
		for(int i=0;i<target->lives;i++){
			l.x = Message_rect.x + Message_rect.w + 4 + i * 22;
			if(target->number<3){
				fig.y = 4 * 32;
				fig.x = 0;
				fig.w = fig.h = 32;
			}
			// cout<<fig.x<<"ao"<<endl;
			// cout<<target->number<<endl;
			SDL_RenderCopy(Game::renderer, target->staticObjTexture, & fig, & l);
		}
		l.y += 10;
		SDL_Rect r;
		r.h = l.h;
		r.y = l.y;
		if(target->snitch_collected){
			l.x = Message_rect.x - 4 - 3 * 25;
			r.x = l.x;
			r.w = l.x+l.w-r.x;
		}
		if(target->broom_collected){
			l.x = Message_rect.x - 4 - 2 * 25;
			if(target->snitch_collected == 0) r.x = l.x;
			r.w = l.x+l.w-r.x;
		}
		if(target->invisible){
			l.x = Message_rect.x - 4 - 25;
			if(target->snitch_collected == 0 and target->broom_collected == 0) r.x = l.x;
			r.w = l.x+l.w-r.x;
		}
		if(Game::server == 0 and Game::client == 0){
			SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(Game::renderer, &r);
			if(target->snitch_collected){
				l.x = Message_rect.x - 4 - 3 * 25;
				SDL_RenderCopy(Game::renderer, snitch, new SDL_Rect{0, 0, 874, 414}, & l);
			}
			if(target->broom_collected){
				l.x = Message_rect.x - 4 - 2 * 25;
				SDL_RenderCopy(Game::renderer, broom, new SDL_Rect{0, 0, 2393, 1274}, & l);
			}
			if(target->invisible){
				l.x = Message_rect.x - 4 - 25;
				SDL_RenderCopy(Game::renderer, cloak, new SDL_Rect{0, 0, 728, 508}, & l);
			}
		}
	}
	else{
		temp = "Dragon " + to_string(target->number - 2);
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Game::font, (temp).c_str(), SDL_Color{255, 255, 255, 255});
		SDL_Texture* Message = Texture::LoadTexture(surfaceMessage);
		SDL_Rect Message_rect;
		int digits = temp.size();
		Message_rect.w = 15 * digits;
		Message_rect.h = 20;
		Message_rect.y = destR.y + 5 + destR.h;
		Message_rect.x = destR.x + length / 2 - Message_rect.w / 2;
		SDL_RenderCopy(Game::renderer, Message, NULL, & Message_rect);
	}
	if((target->number == 1 or target->number == 2) and target->boost){
		string temp = "Boost: " + to_string(int(target->boost_time_left));
		SDL_Color color = SDL_Color{255, 255, 255, 255};
		if(target->boost_time_left < 10){
			color = SDL_Color{255, 0, 0, 255};
		}
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Game::font, (temp).c_str(), color);
		SDL_Texture* Message = Texture::LoadTexture(surfaceMessage);
		SDL_Rect Message_rect;
		int digits = temp.size();
		Message_rect.w = 15 * digits;
		Message_rect.h = 20;
		Message_rect.y = destR.y + 5 + destR.h + 25;
		Message_rect.x = destR.x + length / 2 - Message_rect.w / 2 + 5;
		SDL_RenderCopy(Game::renderer, Message, NULL, & Message_rect);
	}
	if(target->number<3){
		if(target->number<3){
			fig.y = 4 * 32;
			fig.x = 0;
			fig.w = fig.h = 32;
		}
		SDL_RenderCopy(Game::renderer, target->staticObjTexture, & fig, & figure);
	}
	else
		SDL_RenderCopy(Game::renderer, target->objTexture, & fig, & figure);
	SDL_Color colorh = SDL_Color{255, 255, 255, 255};
	if(health < 10){
		colorh = SDL_Color{255, 0, 0, 255};
	}
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Game::font, (to_string(health) + " %").c_str(), colorh);
	SDL_Texture* Message = Texture::LoadTexture(surfaceMessage);

	SDL_Rect Message_rect;
	int digits = max((int)log10(health) + 1, 1) + 2;
	Message_rect.w = 15 * digits;
	Message_rect.h = 20;
	Message_rect.y = destR.y + destR.h / 2 - Message_rect.h / 2;
	if(target->number % 2 == 1) Message_rect.x = destR.x + length + thick + 10;
	else Message_rect.x = destR.x - thick - 10 - Message_rect.w;
	
	SDL_RenderCopy(Game::renderer, Message, NULL, & Message_rect);
	if(health > 0 and health < 10 and target->number < 3){
		colorh = SDL_Color{255, 0, 0, 255};
		surfaceMessage = TTF_RenderText_Solid(Game::font, "Danger!!", colorh);
		Message = Texture::LoadTexture(surfaceMessage);
		digits = 8;
		Message_rect.y = destR.y + destR.h / 2 - Message_rect.h / 2;
		if(target->number % 2 == 1) Message_rect.x += 10 + Message_rect.w;
		else Message_rect.x -= (10 + 15 * digits);
		Message_rect.w = 15 * digits;
		Message_rect.h = 20;
		if(counter++ < Game::FPS/2){
			SDL_RenderCopy(Game::renderer, Message, NULL, & Message_rect);
		}
		if(counter == Game::FPS) counter = 0;
	}
}