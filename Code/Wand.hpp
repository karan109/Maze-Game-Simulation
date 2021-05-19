#pragma once

#include "Entity.hpp"

class Wand: public Entity{
public:

void Delete();
Wand (SDL_Rect srcR_param, int start);
void Update();

};