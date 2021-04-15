#include "Collision.hpp"

int Collision::AABB(const SDL_Rect & A, const SDL_Rect & B){
	if(A.x + A.w >= B.x and B.x + B.w >= A.x and A.y + A.h >= B.y and B.y + B.h >= A.y){
		if(A.x <= B.x and ((A.y >= B.y and A.y <= B.y + B.h) or (A.y + A.h >= B.y and A.y + A.h <= B.y + B.h))){
			return 1;
		}
		if(A.x >= B.x + B.w and ((A.y >= B.y and A.y <= B.y + B.h) or (A.y + A.h >= B.y and A.y + A.h <= B.y + B.h))){
			return 2;
		}
		if(A.y <= B.y and ((A.x >= B.x and A.x <= B.x + B.w) or (A.x + A.w >= B.x and A.x + A.w <= B.x + B.w))){
			return 3;
		}
		if(A.y >= B.y + B.h and ((A.x >= B.x and A.x <= B.x + B.w) or (A.x + A.w >= B.x and A.x + A.w <= B.x + B.w))){
			return 4;
		}
	}
	return 0;
	// if(A.x + A.w >= B.x and B.x + B.w >= A.x and A.y + A.h >= B.y and B.y + B.h >= A.y){
	// 	return true;
	// }
	// else{
	// 	return false;
	// }
}