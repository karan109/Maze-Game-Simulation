#pragma once

#include "includes.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Wall.hpp"
#include "Drone.hpp"
#include "Monster.hpp"
#include "Stone.hpp"
#include "Remote.hpp"
#include "Snitch.hpp"
#include "Health.hpp"
#include "Broom.hpp"



// Maintain a list of all entities
class Entities{
public:
	vector<Player * > * players;
	vector<Wall * > * walls;
	vector<Drone * > * drones;
	vector<Monster * > * monsters;
	vector<Stone * > * stones;
	vector<Remote * > * remotes;
	vector<Snitch * > * snitches;
	vector<Health * > * healths;
	vector<Broom * > * brooms;

	Entities(){
		players = new vector<Player *>(0);
		walls = new vector<Wall *>(0);
		drones = new vector<Drone *>(0);
		monsters = new vector<Monster *>(0);
		stones = new vector<Stone *>(0);
		remotes = new vector<Remote *>(0);
		snitches = new vector<Snitch *>(0);
		healths = new vector<Health *>(0);
		brooms = new vector<Broom *>(0);

	}
	void Add(Player * player){
		players->push_back(player);
	}
	void Add(Remote * remote){
		remotes->push_back(remote);
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
	void Add(Snitch * snitch){
		snitches->push_back(snitch);
	}
	void Add(Health * health){
		healths->push_back(health);
	}

	void Add(Broom * broom){
		brooms->push_back(broom);
	}

	void Delete (Broom * broom) {
		auto position = find (brooms->begin(), brooms->end(), broom);
		if (position != brooms->end()) brooms->erase(position);
	}

	void Delete (Snitch * snitch) {
		auto position = find (snitches->begin(), snitches->end(), snitch);
		if (position != snitches->end()) snitches->erase(position);
	}

	void Delete (Monster * monster) {
		auto position = find (monsters->begin(), monsters->end(), monster);
		if (position != monsters->end()) monsters->erase(position);
	}

	void Delete (Player * player) {
		auto position = find (players->begin(), players->end(), player);
		if (position != players->end()) players->erase(position);
	}

};