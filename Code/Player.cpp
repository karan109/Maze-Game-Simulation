#include "Player.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Entities.hpp"
#include "Spell.hpp"
#include "Texture.hpp"

void Player::Delete() {
	// SDL_DestroyTexture(objTexture);
	Game::entities->Delete(health_box);
	Game::entities->Delete(static_health_box);
	Game::entities->Delete(this);
	// what if this is the target of something?
}

Player::Player(SDL_Rect srcR_param, int start, int number_param) : Entity("../Images/pacman.png", srcR_param, start){
	original_speed = Game::player_original_speed;
	speed = original_speed;
	boost_speed = Game::player_boost_speed;
	boost_time_limit = Game::player_boost_time_limit;
	original_mode = -1;
	set_mode(original_mode); //mode = -1;
	dest = retreat_node;
	Entity::boost_time_left = 0;



	showHealth = true;
	health = 100;
	health_dps = Game::player_health_decrement_per_second;
	if(Game::server or Game::client) health_dps = 0;
	number = number_param;
	if(showHealth){
		health_box = new Health(srcR_param, this, true);
		static_health_box = new Health(srcR_param, this, false);
		Game::entities->Add(health_box);
		Game::entities->Add(static_health_box);
	}
}

Player::Player(SDL_Rect srcR_param, int start, int number_param, int frames_param, int speed_param, int type_param) : Entity(("../Images/"+Game::player_name+".png").c_str(), srcR_param, start){
	player_name = Game::player_name;
	if(type_param == 0) player_name = Game::remote_name;
	if(player_name == "harry1") player_name = "Harry";
	if(player_name == "ron") player_name = "Ron";
	if(player_name == "hermione") player_name = "Hermione";
	if(type_param == 0){ 
		objTexture = Texture::LoadTexture(("../Images/"+Game::remote_name+".png").c_str());
		Entity::staticObjTexture = Texture::LoadTexture(("../Images/"+Game::remote_name+".png").c_str());
	}
	original_speed = Game::player_original_speed;
	speed = original_speed;
	boost_speed = Game::player_boost_speed;
	boost_time_limit = Game::player_boost_time_limit;
	original_mode = -1;
	set_mode(original_mode); //mode = -1;
	dest = retreat_node;
	Entity::boost_time_left = 0;
	type = type_param;

	animated = true;
	srcR.y = srcR.h * 4;
	frames = frames_param;
	animate_speed = speed_param;
	showHealth = true;
	health = 100;
	health_dps = Game::player_health_decrement_per_second;
	if(Game::server or Game::client) health_dps = 0;
	number = number_param;
	if(showHealth){
		health_box = new Health(srcR_param, this, true);
		static_health_box = new Health(srcR_param, this, false);
		Game::entities->Add(health_box);
		Game::entities->Add(static_health_box);
	}
}


void Player::Update(){

	// cout << xpos << " " << destR.x << " " << ypos << " " <<destR.y << endl;

	// time_update();
	if (! collided) {


		if (getBlock() == Game::cloak_node) {
			invisible = 1;
			if(Game::server == 0 and Game::client == 0)
				Entity::change_objTexture("../Images/cloak.png", SDL_Rect{0, 0, 512, 512}, destR);
			else{
				if(number == 1)
					Entity::change_objTexture("../Images/cloak.png", SDL_Rect{0, 0, 512, 512}, destR);
				else{
					Entity::change_objTexture("../Images/empty.png", SDL_Rect{0, 0, 32, 32}, destR);
					// health_box->show = false;
				}
			}
			animated = false;
			Game::cloak_node = -1;
			Mix_PlayChannel( -1, Game::gMedium, 0 );
			Game::display_message(player_name+" has captured the invisibility cloak!", "Use it wisely");

		}

		for(auto & wand: * Game::entities->wands){
			int dir = Collision::close_AABB(wand->getBB(), getBB(), wand->getXV(), wand->getYV(), getXV(), getYV());
			if(dir != 0) {
				wand_caught = 1;
				wand->Delete();
				Mix_PlayChannel( -1, Game::gMedium, 0 );
				Game::display_message(player_name+" has the power of the elder wand!");
			}
		}

	}
	update_boost();

	if (casting_conditions()) {
		// cout << 1 << endl;
		cast_spell();
	}

	if(animated){
		srcR.x = srcR.w * ( (int) (SDL_GetTicks() / animate_speed) ) % frames;
	}
	if(type == 1){
		Entity::Update();
	}
	else{
		time_update();

		Entity::keepInside();
		if (mode != -1) handle_wall_collisions();

		if (mode == -1) {
			Update_remote();
			// else{
			// 	Update_remote();
			// }
		}

		if (mode == 0) {
			Update0();
		}

		if (mode == 1) {
			Update1();
		}

		if (mode == 2) {
			Update2();
		}

		if (mode == 3) {
			Update3();
		}

		if (mode == 4) {
			Update4();
		}
	}
	
	// face = 1 right facing
	// face = 2 left facing
	// face = 3 down facing
	// face = 4 up facing
	if (! invisible) {
		if(yv > 0){
			srcR.y = srcR.h * 4;
			face = 3;
			if(! animated) srcR.x = 0;
			animated = true;
		}
		else if(yv < 0){
			srcR.y = srcR.h * 7;
			face = 4;
			if(! animated) srcR.x = 0;
			animated = true;
		}
		else if(xv > 0){
			srcR.y = srcR.h * 6;
			face = 1;
			if(! animated) srcR.x = 0;
			animated = true;
		}
		else if(xv < 0){
			srcR.y = srcR.h * 5;
			face = 2;
			if(! animated) srcR.x = 0;
			animated = true;
		}
		else{
			// srcR.y = srcR.h * 4;
			// srcR.x = srcR.w * 7;
			animated = false;
		}
	}

	handle_spell_collisions();


	if (fmod(entity_time, 1.0) == 0) {
		decrease_health(health_dps);
	}

	handle_spell_collisions();
}


void Player::boost_on() {
	scary = 1;
	Entity::boost = 1;
	speed = boost_speed;
	Entity::boost_time_left = boost_time_limit; // is reset to max val when 2nd boost even if first not over
}


void Player::boost_off() {
	scary = 0;
	Entity::boost = 0;
	speed = original_speed;
	Entity::boost_time_left = 0;
	// Game::game_pause(1);
}



void Player::update_boost_time_left() {
	// display only ceil(boost_time_left)
	Entity::boost_time_left -= (double) 1 / Game::FPS;
	// cout << boost_time_left << endl;
}

void Player::update_boost() {
	if (!Entity::boost) return;
	// display_boost();
	update_boost_time_left();
	if (Entity::boost_time_left <= 0) {
		boost_off();
	}

}


bool Player::casting_conditions() {
	// if wand is not caught
	if (!wand_caught) return 0 ;
	// cout << " player casting condition used";


	if(Game::event.type == SDL_KEYDOWN){
		auto key = Game::event.key.keysym.sym;
		if(key == SDLK_SPACE)  {
			if (Game::spacebar_pressed == 0 and type == 1) {
				// cout<<"ok"<<endl;
				// Game::spacebar_pressed = 1;
				Mix_PlayChannel( -1, Game::gLow, 0 );
				Game::weapon = 1;
				return 1;
			}
		}
	}
	if(Game::weapon_rec == 1 and Game::remote_spacebar_pressed == 0 and type == 0){
		cout<<"throw"<<endl;
		return 1;
	} 

	return 0;	
}



void Player::cast_spell() {
	Spell * spell = new Spell(this);
	Game::entities->Add(spell);
	// add spell to entities
}


void Player::handle_spell_collisions() {
	spell_collision = 0;

	if (invisible) return;
	
	for(auto & spell: * Game::entities->spells){
		if (spell->wizard == this and spell->released == 0) continue;
		int dir = Collision::AABB(getBB(), spell->getBB(), getXV(), getYV(), spell->getXV(), spell->getYV());
		SDL_Rect R = this->getBB();
		// SDL_Rect S = spell->getBB();
		// cout << "R " << R.x << " " << R.x + R.w << " " << R.y << " " << R.y + R.h << endl;
		// cout << "S " << S.x << " " << S.x + S.w << " " << S.y << " " << S.y + S.h << " " << spell->xv << " " << spell-> yv << " " << dir << endl ;
		if (dir != 0) {
			// collided = 1;
			// assert (dir == face)
			if(number == 1) Mix_PlayChannel( -1, Game::player_hit, 0 );
			switch (spell->face) {
				case 1: spell->head = R.x; break;
				case 2: spell->head = R.x + R.w; break;
				case 3: spell->head = R.y; break;
				case 4: spell->head = R.y + R.h; break;
			}
			spell_collision = 1;
			decrease_health(0.5);
			spell->update_destR();
		}
	}
}



// void Player::Health0 () {
// 	if (health == 0) {
// 		lives -= 1;
// 		collided = 1;
// 		Game::collision_happened = 1;
// 		Game::collided_player = this;
// 		Game:collision_code = "player_dead";
// 		// if (lives == 0) {
// 		// 	// blink and stuff
// 		// 	Delete();
// 		// }
// 		// else {
// 		// 	// display_message  #lives remaining.
// 		// 	// increase health and game pause
// 		// }
// 	}
// }









