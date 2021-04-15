#pragma once

#include "includes.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Wall.hpp"

class Entities{
public:
	vector<Player * > * players;
	vector<Wall * > * walls;
	Entities(){
		players = new vector<Player *>(0);
		walls = new vector<Wall *>(0);
	}
	void Add(Player * player){
		players->push_back(player);
	}
	void Add(Wall * wall){
		walls->push_back(wall);
	}
};