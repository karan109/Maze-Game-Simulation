#pragma once

#include "includes.hpp"
#include "Entity.hpp"


class Collision{
public:
	// Detects collision between 2 objects bounding boxes A and B, with velocities given
	static int AABB(const SDL_Rect & A, const SDL_Rect & B, const int xv, const int yv, const int xv1 = 0, const int yv1 = 0);
	// implement closer collisions
	static bool happens (Entity * e1, Entity * e2);
};