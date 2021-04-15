#include "Collision.hpp"

bool Collision::AABB(const SDL_Rect & A, const SDL_Rect & B){
	if(A.x + A.w >= B.x and B.x + B.w >= A.x and A.y + A.h >= B.y and B.y + B.h >= A.y){
		return true;
	}
	else{
		return false;
	}
}