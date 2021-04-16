#pragma once

#include "includes.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Wall.hpp"
#include "Drone.hpp"

class Entities{
public:
	vector<Player * > * players;
	vector<Wall * > * walls;
	vector<Drone * > * drones;
	Entities(){
		players = new vector<Player *>(0);
		walls = new vector<Wall *>(0);
		drones = new vector<Drone *>(0);
	}
	void Add(Player * player){
		players->push_back(player);
	}
	void Add(Drone * drone){
		drones->push_back(drone);
	}
	void Add(Wall * wall){
		walls->push_back(wall);
	}
};