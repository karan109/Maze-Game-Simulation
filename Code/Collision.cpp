#include "Collision.hpp"

// Detects collision between 2 objects bounding boxes A and B, with velocities given
// 1 if ->| (left)
// 2 if |<- (right)
// 3 if down
// 4 if up
// 0 if no collision
int Collision::AABB(const SDL_Rect & A, const SDL_Rect & B, const int xv, const int yv, const int xv1, const int yv1){
	if(A.x + A.w >= B.x and B.x + B.w >= A.x and A.y + A.h >= B.y and B.y + B.h >= A.y){
		if(xv > 0 or xv1 < 0) return 1;
		if(yv > 0 or yv1 < 0) return 3;
		if(xv < 0 or xv1 > 0) return 2;
		if(yv < 0 or yv1 > 0) return 4;
	}
	return 0;
}

bool Collision::happens (Entity * e1, Entity * e2) {
	return  (Collision::AABB(e1->getBB(), e2->getBB(), e1->getXV(), e2->getYV(), e1->getXV(), e2->getYV()) != 0);
}
