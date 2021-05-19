#pragma once

#include "Entity.hpp"

class Wand: public Entity{
public:

static int num_wands;
int wand_number = 0;
void Delete();
Wand (SDL_Rect srcR_param, int start);
void Update();

};