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
// close collision
int Collision::close_AABB(const SDL_Rect & A, const SDL_Rect & B, const int xv, const int yv, const int xv1, const int yv1){
	int a1, a2, b1, b2, c1, c2, A1, A2, B1, B2, C1, C2;
	int distance = 10;
	bool x_collision, y_collision;
	a1 = A.x;
	a2 = A.x + A.w;
	b1 = B.x;
	b2 = B.x + B.w;
	c1 = a2 - b1;
	c2 = b2 - a1;
	x_collision = (c1 >= distance and c2 >= distance);
	A1 = A.y;
	A2 = A.y + A.h;
	B1 = B.y;
	B2 = B.y + B.h;
	C1 = A2 - B1;
	C2 = B2 - A1;
	y_collision = (C1 >= distance and C2 >= distance);

	if(x_collision and y_collision){
		// cout << a1 << " " << a2  << " " << b1 << " " << b2 << c1  << " " << c2 << endl;
		// cout << A1 << " " << A2 << " " << B1 << " " << B2 << C1 <<  " " << C2 << endl;
		// cout << 1 << endl;
		if(xv > 0 or xv1 < 0) return 1;
		if(yv > 0 or yv1 < 0) return 3;
		if(xv < 0 or xv1 > 0) return 2;
		if(yv < 0 or yv1 > 0) return 4;
	}
	return 0;
	// cout << 0 << endl;
}

bool Collision::happens (Entity * e1, Entity * e2) {
	return  (Collision::AABB(e1->getBB(), e2->getBB(), e1->getXV(), e2->getYV(), e1->getXV(), e2->getYV()) != 0);
}
