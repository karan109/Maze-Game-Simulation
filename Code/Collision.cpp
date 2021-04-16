#include "Collision.hpp"

int Collision::AABB(const SDL_Rect & A, const SDL_Rect & B, const int xv, const int yv){
	if(A.x + A.w >= B.x and B.x + B.w >= A.x and A.y + A.h >= B.y and B.y + B.h >= A.y){
		if(xv > 0) return 1;
		if(yv > 0) return 3;
	}
	if(B.x + B.w >= A.x and A.x + A.w >= B.x and B.y + B.h >= A.y and A.y + A.h >= B.y){
		if(xv < 0) return 2;
		if(yv < 0) return 4;
	}
	return 0;
}