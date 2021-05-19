#include "Entity.hpp"
#include "Texture.hpp"
#include "Collision.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Drone.hpp"
#include "Monster.hpp"
#include "Stone.hpp"
#include "Snitch.hpp"
#include "Broom.hpp"
// #include "Remote.hpp"
// #include "Spell.hpp"
#include "Wand.hpp"


Maze * Game::game_maze = new Maze();
SDL_Renderer * Game::renderer = nullptr;
SDL_Texture * Game::background = nullptr;
SDL_Event Game::event;

// Initialize entities object to store all entities
Entities * Game::entities = new Entities();
TTF_Font* Game::font;
// Constants
int Game::width;
int Game::height;
int Game::rows = 12;
int Game::cols = 25;
int Game::original_h = 32;
int Game::original_w = 32;
int Game::block_h = 32;
int Game::block_w = 32;
int Game::wall_thickness = 16;
bool Game::no_trap = true;
int Game::player_h = 30;
int Game::player_w = 30;
int Game::original_player_h = 32;
int Game::original_player_w = 32;
int Game::stone_w = 32;
int Game::stone_h = 32;
int Game::num_stones = 7;
int Game::menu = 160;
bool Game::isRunning = false;
int Game::quit = 0;
// int Game::seed = 0;
int Game::seed = time(0);
int Game::response = 0;
int Game::send = 0;
bool Game::server = false;
bool Game::client = false;
int Game::weapon = 0;
int Game::weapon_rec = 0;
int Game::win = 0;
string Game::message = "";
double Game::message_t = 2.5;
int Game::message_counter = 0;
int Game::FPS = 60;
int Game::frameDelay = 1000 / FPS;
int Game::window_h = Game::wall_thickness + Game::menu + block_h * rows + (rows - 1) * wall_thickness;
int Game::window_w = 2 * Game::wall_thickness + block_w * cols + (cols - 1) * wall_thickness;
int Game::N = Game::rows * Game::cols;

int Game::original_snitch_w = 874;
int Game::original_snitch_h = 414;
int Game::original_wand_w = 860;
int Game::original_wand_h = 900;
int Game::task;
string Game::player_name = "";
string Game::remote_name = "";
Mix_Music * Game::gMusic = nullptr;
Mix_Chunk * Game::gScratch = nullptr;
Mix_Chunk * Game::gHigh = nullptr;
Mix_Chunk * Game::gMedium = nullptr;
Mix_Chunk * Game::gLow = nullptr;
Mix_Chunk * Game::player_hit = nullptr;
Mix_Chunk * Game::player_monster = nullptr;
Mix_Chunk * Game::game_win = nullptr;
Mix_Chunk * Game::game_lose = nullptr;
Mix_Chunk * Game::player_scary = nullptr;
Mix_Music * Game::ending = nullptr;

int Game::original_broom_h = 1274;
int Game::original_broom_w = 2393;
// bool Game::broom_exists = 0;

double Game::global_pause_time_variable = 0;
bool Game::spacebar_pressed = 0;
bool Game::remote_spacebar_pressed = 0;
bool Game::paused = false;
bool Game::collision_happened = false;


int Game::global_counter = 0;
double Game::global_time = 0;
int Game::pause_counter = 0;
double Game::pause_time = 0;
int Game::collision_counter = 0;
double Game::collision_time = 0;


double Game::player_monster_collision_pause = 1;
double Game::player_snitch_collision_pause = 1;
double Game::player_broom_collision_pause = 0;
double Game::player_dead_collision_pause = 2;
double Game::player_not_dead_collision_pause = 0;
double Game::monster_dead_collision_pause = 2;
double Game::win_pause = 2;





double Game::monster_original_speed = 2;
double Game::snitch_original_speed = 1.5;
double Game::player_original_speed = 3.5;

double Game::player_boost_speed = 5;
double Game::player_boost_time_limit = 20;

int Game::broom_apparatation_time = 10;
int Game::broom_disapparation_time = 20; 
int Game::monster_cycle_time = 30;

// ------------------------------------------------- variables --------------------------------------------------


int Game::broom_starting_node = 25; //( Game::rows/2 ) * (Game::cols) + (Game::cols/2);
int Game::monster1_starting_node = Game::rows * Game::cols - 1; // change to Game::rows * Game::cols - 1
int Game::player1_starting_node = 0;
int Game::snitch_starting_node = 20;
int Game::monster2_starting_node = Game::N - Game::cols; //bottom left corner


double Game::player_health_decrement_per_second = (double)100 / (5*60); //over in 60 seconds
// int Game::cloak_node = random_number();
int Game::cloak_node = 10;
int Game::wand_starting_node = 184;
// ----------------------------------------------------------------------------------------------------------------

int Game::random_number() {
	return rand() % Game::N;
}
// vector<pair<int, int>> Game::generate_sequence(int exist_time, int max_buffer);
vector<pair<int, int>> Game::generate_sequence(int exist_time, int max_buffer){
	srand(Game::seed);
	vector<pair<int, int>> result;
	int prev = 0;
	while(1){
		int next = rand()%max_buffer + prev;
		if(prev != 0) next += exist_time;
		if(next > 2000) break;
		// 600 is 10 minutes
		result.push_back({next, rand()%N});
		prev = next;
	}
	return result;
}

int Game::broom_seq_counter = 0;
vector<pair<int, int>> Game::broom_seq;
int Game::wand_seq_counter = 0;
vector<pair<int, int>> Game::wand_seq;
void Game::show(vector<pair<int, int>> a) {
	cout << "[ ";
	for (int i = 0; i < a.size() ; ++i) {
		cout << "(" << a[i].first << ", " << a[i].second << ")  ";
	}
	cout << " ]";
	cout << endl << endl;
} 


SDL_Texture * background;
SDL_Surface* surfaceMessage;
SDL_Texture* Message;
SDL_Rect Message_rect;
int message_type = 0;
string message_aux = "";

Game::Game(){

}
Game::~Game(){

}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscrean){
	// cout<<"ok"<<endl;
	// auto temp = generate_sequence(20, 30);
	// for(auto u:temp)cout<<u.first<<" "<<u.second<<endl;
	// cout << "wand_starting_node " << wand_starting_node << endl;
	// cout << "cloak_node " << cloak_node << endl;

	broom_seq = Game::generate_sequence(25, 20);
	wand_seq = Game::generate_sequence(30, 30);

	// show(broom_seq);

	if(task == 2) no_trap = false;
	Game::width = width;
	Game::height = height;
	int flags = 0;
	if(fullscrean){
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if(isRunning){
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if(renderer){
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
	}
	srand(Game::seed);
	Game::game_maze = new Maze();
	if(Game::task == 2){
		for(int i=0;i<num_stones;i++){
			stone = new Stone("../Images/stone2.png", SDL_Rect{0, 0, 353, 300}, rand() % (Game::rows * Game::cols), 15, 15);
			entities->Add(stone);
		}
		drone = new Drone(SDL_Rect{144, 288, 72, 72}, 0);
		entities->Add(drone);
	}


	if(Game::task == 1){
		// must add player before monster (not neccessary anymore)
		// 0 is the number_param

 		if(Game::server){
 			message = "Defeat the other player!";
 			add_player(player1_starting_node, 1);
            player2 = new Player(SDL_Rect{0, 0, Game::original_player_h, Game::original_player_w}, Game::cols-1, 2, 6, 100, 0);
            entities->Add(player2);
            // player_health_decrement_per_second = 0;
        }
        else if(Game::client){
        	message = "Defeat the other player!";
        	add_player(Game::cols-1, 1);
            player2 = new Player(SDL_Rect{0, 0, Game::original_player_h, Game::original_player_w}, player1_starting_node, 2, 6, 100, 0);
            entities->Add(player2);
            // player_health_decrement_per_second = 0;
        }

        else{

        	message = "Collect the wand, stone and the cloak!";
        	add_player(player1_starting_node, 1);
        	srand(time(0));
        	Game::seed = rand()%100000;
        }
		add_monster(monster1_starting_node, 0.5, 1, 4);
		// add_monster(monster2_starting_node, 0.3, 0, 3);
		add_snitch(snitch_starting_node);
		add_wand(wand_starting_node);
        


		surfaceMessage = TTF_RenderText_Solid(Game::font, (message).c_str(), SDL_Color{255, 255, 255, 255});
		Message = Texture::LoadTexture(surfaceMessage);
		Message_rect.w = 15 * message.size();
		Message_rect.h = 20;
		Message_rect.y = 20;
		Message_rect.x = window_w/2 - Message_rect.w / 2;
	}
	



	if(!Game::server and !Game::client){
		rows = 12;
		cols = 25;
		
		Game::N = Game::rows * Game::cols;
	}

	Game::game_maze->DrawMaze();

	gMusic = Mix_LoadMUS( "../Music/bgm2.wav" );
	gScratch = Mix_LoadWAV( "../Music/wall_collide.wav" );
	gHigh = Mix_LoadWAV( "../Music/reward.wav" );
	gMedium = Mix_LoadWAV( "../Music/collect.wav" );
	gLow = Mix_LoadWAV( "../Music/shoot.wav" );
	player_hit = Mix_LoadWAV( "../Music/player_hit.wav" );
	player_monster = Mix_LoadWAV( "../Music/player_monster.wav" );
	game_win = Mix_LoadWAV( "../Music/game_win.wav" );
	game_lose = Mix_LoadWAV( "../Music/game_lose.wav" );
	player_scary = Mix_LoadWAV( "../Music/player_scary.wav" );
	background = Texture::LoadTexture("../Images/bg3.jpg");
	ending = Mix_LoadMUS( "../Music/ending.wav" );
}

// ------------------------------------------------- Add entities--------------------------------------------------

void Game::add_monster(int start, double p, bool chase = 1, int number_param = 3) {
	monster = new Monster(SDL_Rect{0, 0, 191, 161}, start, 3, 100, chase, number_param); 
	if(number_param == 3) monster1 = monster;
	else monster2 = monster;
	// monster_set_target(); monster_set_scary_target();done in constructor
	monster->mode = (chase) ? 0 : 2;
	monster->seq = seq_generator(p, chase, 30); 
	// print_queue(monster->seq);
	entities->Add(monster);
}
void Game::add_player(int start, int number_param = 0){
	player1 = new Player(SDL_Rect{0, 0, Game::original_player_h, Game::original_player_w}, start, number_param, 6, 100);
	entities->Add(player1); 

}
void Game::add_snitch(int start){
	snitch = new Snitch(SDL_Rect{0, 0, original_snitch_w, original_snitch_h}, start);
	// snitch->scary_target = player1; // set in snitch constructor
	entities->Add(snitch);
}
void Game::add_wand(int start){
	wand = new Wand(SDL_Rect{0, 0, original_wand_w, original_wand_h}, start);
	entities->Add(wand);
}

void Game::add_broom(int start) {
	broom = new Broom(SDL_Rect{0, 0, original_broom_w, original_broom_h}, start);//(Game::rows * Game::cols / 2)
	entities->Add(broom);
}

void Game::Add_entities() {
	// add broom
	if(task == 1){
		if (broom_seq_counter < broom_seq.size() and global_time == broom_seq[broom_seq_counter].first ) {
			display_message("a broom just apparated");
			add_broom(broom_seq[broom_seq_counter].second);
			broom_seq_counter++;
		}

		if (wand_seq_counter < wand_seq.size() and global_time == wand_seq[wand_seq_counter].first and unwanded_player_exists() and entities->wands->size() == 0) {
			display_message("we have another wand for you");
			add_wand(wand_seq[wand_seq_counter].second);
			wand_seq_counter++;
		}

	}
}
bool Game::unwanded_player_exists() {
	for(auto & player : * entities->players){
		if (player->wand_caught == 0) {
			return 0;
		}
	}
}

// ------------------------------------------------- update running times--------------------------------------------------
void Game::update_global_running_time() {
	global_counter++;
	global_time = (double)global_counter / Game::FPS;
}

void Game::update_global_pause_time() {
	pause_counter++;
	pause_time = (double) pause_counter / Game::FPS;
}
void Game::update_global_collision_time() {
	collision_counter++;
	collision_time = (double) collision_counter / Game::FPS;
}



// ------------------------------------------------- switch pauses --------------------------------------------------

void Game::switch_pause() {

	bool resume = (pause_time >= global_pause_time_variable);

	if (resume) {
		paused = false;
		pause_counter = 0;
		pause_time = 0;
		global_pause_time_variable = 0;

		reset_collided_entities();

	}
}
void Game::switch_collision() {
	// first get peeps to their place
	// then wait for 1/2/5 sec
	// then reset.
	bool resume = resume_safely(); //can make changes in resume safely that snitch takes 5 secs
	if (resume) {
		collision_happened = false;
		collision_counter = 0;
		collision_time = 0;

		collision_pause();
		// reset_collided_entities(); //done in switch_pause now
	}
}


// ------------------------------------------------- helper functions --------------------------------------------------


void Game::handle_quit_game () {
	SDL_PollEvent(& event);
	if(event.type == SDL_QUIT){
		isRunning = false;
	}
	quit = 1;
	// cout<<"quit badddd"<<endl;
}


void Game::game_pause(double t) {
	// if (paused == 1) return;
	global_pause_time_variable = t;
	paused = 1;
}

void Game::clean(){
	// Mix_PlayChannel( -1, Game::game_lose, 0 );
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	// Mix_Quit();
	// IMG_Quit();
	// TTF_Quit();
	// SDL_Quit();
}


// ------------------------------------------------- game loop functions --------------------------------------------------



void Game::handleEvents(){

	handle_quit_game();

	if (paused) {
		update_global_pause_time();
		switch_pause();
	}
	else if (collision_happened) {
		update_global_collision_time();
		switch_collision();

	}
	else {
		update_global_running_time();
	}

}


void Game::update(){

	message_counter++;
	if(message_counter > FPS * message_t){
		if(message_type == 0){
			message = "";
		}
		else{
			message_type = 0;
			message = message_aux;
			message_aux = "";
		}
		message_counter = 0;
		surfaceMessage = TTF_RenderText_Solid(Game::font, (message).c_str(), SDL_Color{255, 255, 255, 255});
		Message = Texture::LoadTexture(surfaceMessage);
		Message_rect.w = 15 * message.size();
		Message_rect.x = window_w/2 - Message_rect.w / 2;
	}
	if (paused) {
		return;
	}

	if (collision_happened) {
		collision_updates();
		return;
	}

	Add_entities();

	for(auto & spell : * entities->spells){
		spell->Update();
	}


	for(auto & stone : * entities->stones){
		stone->Update();
	}
	for(auto & player : * entities->players){
		player->Update();
	}
	// for(auto & remote : * entities->remotes){
	// 	remote->Update();
	// }
	for(auto & monster : * entities->monsters){
		monster->Update();
	}
	for(auto & drone : * entities->drones){
		drone->Update();
	}
	for(auto & snitch : * entities->snitches){
		snitch->Update();
	}
	for(auto & health : * entities->healths){
		health->Update();
	}

	for(auto & broom : * entities->brooms){
		broom->Update();
	}

	for(auto & wand : * entities->wands){
		wand->Update();
	}

}



void Game::render(){
	SDL_RenderClear(renderer);
	if(task == 1){
		Texture::Draw(background, SDL_Rect{0, 0, 533, 300}, SDL_Rect{0, 0, width, height});
	}
	else{
		
	}
	auto black = Texture::LoadTexture("../Images/black.png");
	Texture::Draw(black, SDL_Rect{0, 0, 32, 32}, SDL_Rect{0, menu - wall_thickness, width, wall_thickness});
	Texture::Draw(black, SDL_Rect{0, 0, 32, 32}, SDL_Rect{0, menu, wall_thickness, height - menu});
	Texture::Draw(black, SDL_Rect{0, 0, 32, 32}, SDL_Rect{width - wall_thickness, menu, wall_thickness, height - menu});
	Texture::Draw(black, SDL_Rect{0, 0, 32, 32}, SDL_Rect{0, height - wall_thickness, width, wall_thickness});
	Game::game_maze->DrawMaze();
	for(auto & stone : * entities->stones){
		stone->Render();
	}
	for(auto & player : * entities->players){
		player->Render();
	}
	// for(auto & remote : * entities->remotes){
	// 	remote->Render();
	// }
	for(auto & monster : * entities->monsters){
		monster->Render();
	}
	for(auto & drone : * entities->drones){
		drone->Render();
	}
	for(auto & snitch : * entities->snitches){
		snitch->Render();
	}
	for(auto & health : * entities->healths){
		health->Render();
	}

	for(auto & broom : * entities->brooms){
		broom->Render();
	}
	for(auto & spell : * entities->spells){
		spell->Render();
	}
	for(auto & wand : * entities->wands){
		wand->Render();
	}
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	if(task == 2){
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, "Simulation", SDL_Color{0, 0, 0, 255});
	    SDL_Texture* Message = Texture::LoadTexture(surfaceMessage);
	    SDL_Rect Message_rect;
	    Message_rect.w = 300;
	    Message_rect.h = 50;
	    Message_rect.y = 10;
	    Message_rect.x = window_w / 2 - Message_rect.w / 2;
	    SDL_RenderCopy(renderer, Message, NULL, & Message_rect);
	}
	SDL_RenderCopy(Game::renderer, Message, NULL, & Message_rect);
	SDL_RenderPresent(renderer);
}


// not more than 1 collision at an instant
void Game::handle_collisions() {

	if (paused || collision_happened) return;

	for(auto & monster: * Game::entities->monsters){

		if (int(monster->health) == 0) {
			collision_code = "monster_dead";
			// player->lives -= 1;
			// player->collided = 1; never calling player-> update
			collision_happened = 1;
			collided_monster = monster;
			display_message("Dragon dead!");
			return;
		}
	}	

	// what if collides with another player?
	// if collides with target then return
	for(auto & player: * Game::entities->players){
		for(auto & monster: * Game::entities->monsters){

			int dir = Collision::close_AABB(monster->getBB(), player->getBB(), monster->getXV(), monster->getYV(), player->getXV(), player->getYV());
			if(dir != 0) {
					if (player->scary) {
						// player has got to the monster
						// monster will vanish and start from beginning
						// player will continue
						// add a game pause where monster blinks and stuff happens?
						// Delete();

						collision_code = "scary_player_monster";
						collided_player = player;
						collided_monster = monster;
						display_message("Nice. "+player->player_name+" has scared the dragon");
						if(player->number == 1) Mix_PlayChannel( -1, Game::player_scary, 0 );
						start_game_collision();
						// collision_between(player, monster);
					}
					else {
						//monster has got to the player
						// player will vanish and start from beginning.
						// monster will continue? not sure
						// monster will emit fire
						// monster will retreat?
						// handle game stuck case
						// change player health decrement 1 life
						// cout << "got ya bitch ";
						collision_code = "monster_player";
						collided_player = player;
						collided_monster = monster;
						display_message("Oops! dragon got to "+player->player_name+"!");
						if(player->number == 1) Mix_PlayChannel( -1, Game::player_monster, 0 );
						start_game_collision();
						// collision_between(player, monster);

		
					}	

				collision_happened = 1;
				return;	
			}
		}


		for(auto & snitch: * Game::entities->snitches){
			int dir = Collision::close_AABB(snitch->getBB(), player->getBB(), snitch->getXV(), snitch->getYV(), player->getXV(), player->getYV());
			if(dir != 0) {

				collision_code = "player_snitch";
				collided_player = player;
				collided_snitch = snitch;
				player->snitch_collected = 1;
				start_game_collision();
				// collision_between(player, snitch);
				Mix_PlayChannel( -1, Game::gMedium, 0 );
				display_message(player->player_name+" has caught the golden snitch", "Resucrection stone was inside the snitch.");
				collision_happened = 1;				
				return;

			}
		}

		for(auto & broom: * Game::entities->brooms){
			int dir = Collision::close_AABB(broom->getBB(), player->getBB(), broom->getXV(), broom->getYV(), player->getXV(), player->getYV());
			if(dir != 0) {

				collision_code = "player_broom";
				collided_player = player;
				collided_broom = broom;
				player->broom_collected = 1;
				start_game_collision();
				// collision_between(player, broom);
				Mix_PlayChannel( -1, Game::gMedium, 0 );
				display_message(player->player_name+" is on the broom. Godspeed. wooosh!");
				collision_happened = 1;
				return;
			}
		}

		if (int(player->health) == 0) {
			collision_code = "player_dead";
			player->lives -= 1;
			// player->collided = 1; never calling player-> update
			collision_happened = 1;
			collided_player = player;
			if (collided_player->lives != 0) {
				display_message("I open at the close. "+player->player_name+" resurrects.");
			}
			else {
				display_message(player->player_name+" dead");
			}
			return;
		}
		if (player->num_hallows_caught == 3) {
			collision_code = "master_of_death";
			collision_happened = 1;
			collided_player = player;
			display_message(player->player_name+" is the master of death.");

		}
	}

	//monster and automated stuff collision
}


// -------------------------------------------------collision auxilaries --------------------------------------------------


void Game::start_game_collision () {

	// Broom * broom = collided_broom;
	// Player * player = collided_player;
	// Monster * monster = collided_monster;
	// Snitch * snitch = collided_snitch;

	if (collision_code == "scary_player_monster") {
		// cout << "before collision " << collided_monster->scatter_reached << endl;

		collided_monster->start_collision();

		// cout << "after collision " << collided_monster->mode << " " << collided_monster->speed << endl;

	}

	if (collision_code == "monster_player") {

		collided_monster->start_collision();
		collided_player->start_collision();	
	}

	if (collision_code == "player_broom") {

		collided_player->boost_on();

	}

	if (collision_code == "player_snitch") {
		//player has caught the snitch
		collided_player-> snitch_caught = 1;
		collided_player-> num_hallows_caught++;

		collided_player-> lives = 3;

		collided_snitch-> caught = 1;
		collided_snitch-> transform();
		//increase lives of player
		collided_player->health = 1;
	}
}

void Game::collision_updates() {
	if (collision_code == "scary_player_monster") {


		collided_monster->Update();
		collided_monster->health_box->Update();
		collided_monster->static_health_box->Update();
		collided_monster->decrease_health(0.1);

		collided_player->increase_health(0.1);

	}
	if (collision_code == "monster_player") {

		collided_player->Update();
		collided_player->health_box->Update();
		collided_player->static_health_box->Update();
		collided_player->decrease_health(0.1);


		collided_monster->Update();
		collided_monster->health_box->Update();
		collided_monster->static_health_box->Update();
		collided_monster->increase_health(0.1);
	}
	if (collision_code == "player_snitch") {
		collided_player->health_box->Update();
		collided_player->static_health_box->Update();
		collided_player->increase_health(0.5);
	}
	if (collision_code == "player_broom") {
	}
	if (collision_code == "player_dead") {
		if (collided_player->lives != 0) {
			collided_player->increase_health(0.5);
		}
		else {
			// blink and stuff deletion sequence
		}
	}
	if (collision_code == "monster_dead") {
		// blink stuff
	}
}


bool Game::resume_safely () {
	if (collision_code == "scary_player_monster") {
		return (collided_monster->scatter_reached);
	}
	if (collision_code == "monster_player") {
		// cout<<"aca"<<endl;
		// cout<<collided_player->scatter_reached<<" "<<collided_monster->scatter_reached<<endl;
		return (collided_player->scatter_reached) && (collided_monster->scatter_reached);
	}
	if (collision_code == "player_snitch") {
		return (collided_player->health == 100);
	}
	if (collision_code == "player_broom") {
		return 1;
	}
	if (collision_code == "player_dead") {
		if (collided_player-> lives != 0) {
			return (collided_player->health == 100);
		}
		else {
			return 1;
		}
	}
	if (collision_code == "monster_dead") {
		return 1;
	}
	return 1;
}

void Game::reset_collided_entities() {
	// change_player_face

	if (collision_code == "scary_player_monster") {
		collided_monster->resume_after_collision();
	}

	if (collision_code == "monster_player") {
		collided_player->resume_after_collision();
		collided_monster->resume_after_collision();

	}
	else if (collision_code == "player_snitch") {

		collided_snitch->Delete();

	}
	else if (collision_code == "player_broom") {
		collided_broom->Delete();
	}

	else if (collision_code == "player_dead") {
		if (collided_player-> lives == 0 ) {
			if (collided_player->number == 1) {
	            win = 0;
	            Mix_PlayChannel( -1, Game::game_lose, 0 );
	        }
	        else {
	            win = 1;
	            Mix_PlayChannel( -1, Game::game_win, 0 );
	        }
			collided_player->Delete();
			// display_message("winning msg");
			cout<<"baddd"<<endl;
			Game::quit = 1;
			Game::isRunning = 0;
		}

	}
	else if (collision_code == "monster_dead") {
		collided_monster->Delete();
		// display_message("dragon dead");
	}
	else if (collision_code == "master_of_death") {
		Game::win = (collided_player->number == 1) ? 1 : 0;
		Game::quit = 1;
		Game::isRunning = 0;

	}


	collision_code = "";

	collided_broom = nullptr;
	collided_player = nullptr;
	collided_monster = nullptr;
	collided_snitch = nullptr;
}

void Game::collision_pause() {
	if (collision_code == "scary_player_monster") {
		game_pause(player_monster_collision_pause);
	}

	if (collision_code == "monster_player") {
		game_pause(player_monster_collision_pause);
	}
	else if (collision_code == "player_snitch") {
		game_pause(player_snitch_collision_pause);
	}
	else if (collision_code == "player_broom") {
		game_pause(player_broom_collision_pause);

	}
	else if (collision_code == "player_dead") {
		int x = (collided_player->lives == 0)? player_dead_collision_pause : player_not_dead_collision_pause;
		game_pause(x);
	}
	else if (collision_code == "monster_dead") {
		game_pause(monster_dead_collision_pause);

	}
	else if (collision_code == "master_of_death") {
		game_pause(win_pause);
	}
}


// -------------------------------------------------monster sequence --------------------------------------------------


queue<int> Game::seq_generator(double p, bool chase = 1, int sampling_time = 60) {
	int N = 100; // gmae runs for N * sampling time seconds ie 100 minutes
	int a[2*N];
	for (int i = 0; i < 2*N; ++i) a[i] = 0;
	int f = p * sampling_time;
	int s = sampling_time - f;
	int x, y;
	if (chase) {
		x = f;
		y = s;
	}
	else {
		x = s;
		y = f;
	}
	for (int i = 0; i < N ; ++i) {
		a[2*i] = x;
		a[2*i + 1] = y;
	}
	for (int i = 1; i < 2*N ; ++i) {
		a[i] += a[i-1];
	}
	queue<int> seq;
	for (int i = 0; i < 2*N ; ++i) {
		seq.push(a[i]);
	}
	return seq;
}

void Game::print_queue(queue<int> q){
	vector<int> temp;
	while(!q.empty()){
		int front = q.front();
		temp.push_back(front);
		cout<<front<<" ";
		q.pop();
	}
	for(auto vertex : temp){
		q.push(vertex);
	}
	// cout << endl;
	cout<<endl<<endl<<endl;
}
void Game::display_message(string text, string text2){
	if(text2 == ""){
		message_type = 0;
	}
	else{
		message_type = 1;
	}
	message = text;
	message_aux = text2;
	message_counter = 0;
	surfaceMessage = TTF_RenderText_Solid(Game::font, (message).c_str(), SDL_Color{255, 255, 255, 255});
	Message = Texture::LoadTexture(surfaceMessage);
	Message_rect.w = 15 * message.size();
	Message_rect.x = window_w/2 - Message_rect.w / 2;
}