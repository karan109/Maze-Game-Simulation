#pragma once

// #include "Entity.hpp"
#include "Player.hpp"


class Spell : public Entity{

public:

Player * wizard;
int original_face;
int	face;
int	offset;
int spell_height = 5;
int tail;
int head;
int	length = 0;
bool released = 0;
int spell_length_limit = 10;
bool finished = 0;

int	head_v;
int	tail_v;

Spell(Player * castee);
void Delete();

void set_velocity();
void initialize_head_tail_velocity();

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
void handle_spell_over();
bool spell_over();
void handle_wall_collision();

};





