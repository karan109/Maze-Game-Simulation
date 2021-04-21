#pragma once

#include "includes.hpp"

class Collision{
public:
	static int AABB(const SDL_Rect & A, const SDL_Rect & B, const int xv, const int yv, const int xv1 = 0, const int yv1 = 0);
};