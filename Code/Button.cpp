#include "Button.hpp"
#include "Game.hpp"
#include "Texture.hpp"

Button::Button(SDL_Rect destR_param, int thickness_param, string text_param){
	destR = destR_param;
	text = text_param;
	thickness = thickness_param;
}
Button::Button(SDL_Renderer * renderer, string character_param, SDL_Rect srcR_param, SDL_Rect destR_param){
	string texturesheet = "../Images/"+character_param;
	if(character_param == "harry") texturesheet += "1";
	texturesheet += ".png";
	objTexture = Texture::LoadTexture(renderer, texturesheet.c_str());
	srcR = srcR_param;
	destR = destR_param;
	image = true;
	if(character_param == "harry") character = "Harry";
	if(character_param == "ron") character = "Ron";
	if(character_param == "hermione") character = "Hermione";
}
bool Button::isInside(int x, int y){
	if(x > destR.x and x < destR.x + destR.w and y > destR.y and y < destR.y + destR.h)
		return true;
	return false;
}
void Button::Render(SDL_Renderer * renderer){
	if(!image){
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderFillRect(renderer, new SDL_Rect{destR.x, destR.y, destR.w, thickness});
		SDL_RenderFillRect(renderer, new SDL_Rect{destR.x, destR.y, thickness, destR.h});
		SDL_RenderFillRect(renderer, new SDL_Rect{destR.x + destR.w - thickness, destR.y, thickness, destR.h});
		SDL_RenderFillRect(renderer, new SDL_Rect{destR.x, destR.y + destR.h - thickness, destR.w, thickness});
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Game::font, text.c_str(), SDL_Color{255, 255, 0, 255});
		SDL_Texture* Message = Texture::LoadTexture(renderer, surfaceMessage);

		SDL_Rect Message_rect;
		int digits = text.size();
		Message_rect.w = min(15 * digits, destR.w - 2 * thickness);
		Message_rect.h = min(30, destR.h - 2 * thickness);
		Message_rect.y = destR.y + destR.h / 2 - Message_rect.h / 2;
		Message_rect.x = destR.x + destR.w / 2 - Message_rect.w / 2;
		
		SDL_RenderCopy(renderer, Message, NULL, & Message_rect);
		return;
	}
	SDL_RenderCopy(renderer, objTexture, & srcR, & destR);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Game::font, character.c_str(), SDL_Color{255, 255, 0, 255});
	SDL_Texture* Message = Texture::LoadTexture(renderer, surfaceMessage);

	SDL_Rect Message_rect;
	int digits = character.size();
	Message_rect.w = 15 * digits;
	Message_rect.h = 30;
	Message_rect.y = destR.y + 10 + destR.h;
	Message_rect.x = destR.x + destR.w / 2 - Message_rect.w / 2;
	if(show){
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderFillRect(renderer, new SDL_Rect{destR.x, destR.y, destR.w, thickness});
		SDL_RenderFillRect(renderer, new SDL_Rect{destR.x, destR.y, thickness, destR.h});
		SDL_RenderFillRect(renderer, new SDL_Rect{destR.x + destR.w - thickness, destR.y, thickness, destR.h});
		SDL_RenderFillRect(renderer, new SDL_Rect{destR.x, destR.y + destR.h - thickness, destR.w, thickness});
	}
	SDL_RenderCopy(renderer, Message, NULL, & Message_rect);
}