#pragma once

// #include "Entity.hpp"
#include "Player.hpp"


class Spell : public Entity{

public:

Player * wizard;
int	face;
int	offset;
int spell_height = 5;
int tail;
int head;
int	length = 0;
bool released = 0;
int spell_length_limit = 10;

Spell(Player * castee);
void set_velocity();
SDL_Rect set_rect();
pair <int, int> getfacepoint();
pair <int, int> get_dir();
int get_tail();
void Update();
void update_head();
void update_tail();
SDL_Rect get_rect();
void release_spell();
void Render();

bool release_conditions();

};





