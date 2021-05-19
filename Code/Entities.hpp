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
#include "Spell.hpp"
#include "Wand.hpp"




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
	vector<Spell * > * spells;
	vector<Wand * > * wands;




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
		spells = new vector<Spell *>(0);
		wands = new vector<Wand *>(0);



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

	void Add(Spell * spell){
		spells->push_back(spell);
	}


	void Add(Wand * wand){
		wands->push_back(wand);
	}

	void Delete(Wand * wand){
		auto position = find (wands->begin(), wands->end(), wand);
		if (position != wands->end()) wands->erase(position);
	}

	void Delete(Spell * spell){
		auto position = find (spells->begin(), spells->end(), spell);
		if (position != spells->end()) spells->erase(position);
	}

	void Delete (Broom * broom) {
		// if (brooms->size() == 0) {cout << "fffffffffffffffffffffffffffffffffffffffffff" << endl ; return;}
		auto position = find (brooms->begin(), brooms->end(), broom);
		if (position != brooms->end()) brooms->erase(position);
	}
	void Delete (Stone * stone) {
		auto position = find (stones->begin(), stones->end(), stone);
		if (position != stones->end()) stones->erase(position);
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
	void Delete (Health * health) {
		auto position = find (healths->begin(), healths->end(), health);
		if (position != healths->end()) healths->erase(position);
	}

};