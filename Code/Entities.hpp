#pragma once

#include "includes.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Wall.hpp"

class Entities{
public:
	vector<Player * > * players;
	vector<Wall * > * walls;
	// static int ct;
	Entities(){
		players = new vector<Player *>(0);
		walls = new vector<Wall *>(0);
		// ct = 0;
	}
	void Add(Player * player){
		// ct++;
		players->push_back(player);
	}
	void Add(Wall * wall){
		
		Entities::walls->push_back(wall);
	}
};
extern Entities * entities;