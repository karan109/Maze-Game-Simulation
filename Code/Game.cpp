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
#include "Remote.hpp"

// #include "Spell.hpp"

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
int Game::menu = 100;
bool Game::isRunning = false;
int Game::seed = 0;
// int Game::seed = time(0);
int Game::response = 0;
int Game::send = 0;

string Game::message = "ok";
double Game::message_t = 2.5;
int Game::message_counter = 0;
int Game::FPS = 60;
int Game::frameDelay = 1000 / FPS;
int Game::window_h = Game::wall_thickness + Game::menu + block_h * rows + (rows - 1) * wall_thickness;
int Game::window_w = 2 * Game::wall_thickness + block_w * cols + (cols - 1) * wall_thickness;
int Game::N = Game::rows * Game::cols;

int Game::original_snitch_h = 414;
int Game::original_snitch_w = 874;
int Game::task;
string Game::player_name = "";

Mix_Music * Game::gMusic = nullptr;
Mix_Chunk * Game::gScratch = nullptr;
Mix_Chunk * Game::gHigh = nullptr;
Mix_Chunk * Game::gMedium = nullptr;
Mix_Chunk * Game::gLow = nullptr;

int Game::original_broom_h = 1274;
int Game::original_broom_w = 2393;
// bool Game::broom_exists = 0;

double Game::global_pause_time_variable = 0;
bool Game::spacebar_pressed = 0;
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


double Game::monster_original_speed = 2.5;
double Game::snitch_original_speed = 1.5;
double Game::player_original_speed = 3.5;

double Game::player_boost_speed = 5;
double Game::player_boost_time_limit = 100;

int Game::broom_apparatation_time = 10;
int Game::broom_disapparation_time = 100; // so 110 pe disappears

int Game::monster_cycle_time = 30;

// ------------------------------------------------- variables --------------------------------------------------


int Game::broom_starting_node = 25; //( Game::rows/2 ) * (Game::cols) + (Game::cols/2);
int Game::monster1_starting_node = 299; // change to Game::rows * Game::cols - 1
int Game::player1_starting_node = 0;
int Game::snitch_starting_node = 20;
int Game::monster2_starting_node = Game::N - Game::cols; //bottom left corner


double Game::player_health_decrement_per_second = (double)100 / (5*60); //over in 60 seconds


// ----------------------------------------------------------------------------------------------------------------


SDL_Texture * background;
SDL_Surface* surfaceMessage;
SDL_Texture* Message;
SDL_Rect Message_rect;

Game::Game(){

}
Game::~Game(){

}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscrean){
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
	// srand(seed);
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
		// must add player before monster
		// 0 is the number_param
 		add_player(player1_starting_node, 1);
		add_monster(monster1_starting_node, 0.5, 1, 0); 
		add_monster(monster2_starting_node, 0.3, 0, 0);

		add_snitch(snitch_starting_node);

		surfaceMessage = TTF_RenderText_Solid(Game::font, (message).c_str(), SDL_Color{255, 255, 255, 255});
		Message = Texture::LoadTexture(surfaceMessage);
		Message_rect.w = 15 * message.size();
		Message_rect.h = 20;
		Message_rect.y = 20;
		Message_rect.x = window_w/2 - Message_rect.w / 2;
	}
	





	Game::game_maze->DrawMaze();

	gMusic = Mix_LoadMUS( "../Music/bgm.wav" );
	gScratch = Mix_LoadWAV( "../Music/wall_collide.wav" );
	gHigh = Mix_LoadWAV( "../Music/reward.wav" );
	background = Texture::LoadTexture("../Images/bg3.jpg");
}

// ------------------------------------------------- Add entities--------------------------------------------------

void Game::add_monster(int start, double p, bool chase = 1, int number_param = 0) {
	monster = new Monster(SDL_Rect{0, 0, 191, 161}, start, 3, 100, chase, number_param); 
	// monster_set_target(); monster_set_scary_target();done in constructor
	monster->mode = (chase) ? 0 : 2;
	monster->seq = seq_generator(p, chase, 10); 
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
void Game::add_broom(int appear_time, int start) {
	if (global_time == appear_time) {
		broom = new Broom(SDL_Rect{0, 0, original_broom_w, original_broom_h}, start);//(Game::rows * Game::cols / 2)
		entities->Add(broom);
		// broom_exists = 1;
	}
}

void Game::Add_entities() {
	// add broom
	if(task == 1){
		add_broom(Game::broom_apparatation_time,broom_starting_node);

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
		// game_pause(1);
	}
}


// ------------------------------------------------- helper functions --------------------------------------------------


void Game::handle_quit_game () {
	SDL_PollEvent(& event);
	if(event.type == SDL_QUIT){
		isRunning = false;
	}
}


void Game::game_pause(double t) {
	// if (paused == 1) return;
	global_pause_time_variable = t;
	paused = 1;
}

void Game::clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}


// ------------------------------------------------- game loop functions --------------------------------------------------



void Game::handleEvents(){

	handle_quit_game();

	if (paused) {
		update_global_pause_time();
		switch_pause();
	}
	if (collision_happened) {
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
		message_counter = 0;
		message = "";
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
						// collided_player = player;
						collided_monster = monster;
						display_message("Nice");
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
						display_message("Got ya bitch");
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
				start_game_collision();
				// collision_between(player, snitch);
				display_message("Snitch taken");
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
				start_game_collision();
				// collision_between(player, broom);
				display_message("Broom taken");
				collision_happened = 1;
				return;
			}
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

		collided_monster->start_collision();
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
}


bool Game::resume_safely () {
	if (collision_code == "scary_player_monster") {
		return (collided_monster->scatter_reached);
	}
	if (collision_code == "monster_player") {
		return (collided_player->scatter_reached) && (collided_monster->scatter_reached);
	}
	if (collision_code == "player_snitch") {
		return (collided_player->health == 100);
	}
	if (collision_code == "player_broom") {
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
void Game::display_message(string text){
	message = text;
	message_counter = 0;
	surfaceMessage = TTF_RenderText_Solid(Game::font, (message).c_str(), SDL_Color{255, 255, 255, 255});
	Message = Texture::LoadTexture(surfaceMessage);
	Message_rect.w = 15 * message.size();
	Message_rect.x = window_w/2 - Message_rect.w / 2;
}