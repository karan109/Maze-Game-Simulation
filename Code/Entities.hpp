#pragma once

#include "includes.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Wall.hpp"
#include "Drone.hpp"
#include "Monster.hpp"
#include "Stone.hpp"

class Entities{
public:
	vector<Player * > * players;
	vector<Wall * > * walls;
	vector<Drone * > * drones;
	vector<Monster * > * monsters;
	vector<Stone * > * stones;
	Entities(){
		players = new vector<Player *>(0);
		walls = new vector<Wall *>(0);
		drones = new vector<Drone *>(0);
		monsters = new vector<Monster *>(0);
		stones = new vector<Stone *>(0);
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
	void Add(Monster * monster){
		monsters->push_back(monster);
	}
	void Add(Stone * stone){
		stones->push_back(stone);
	}

};