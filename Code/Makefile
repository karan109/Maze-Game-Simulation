CC := g++
CFLAGS := -std=c++11 -w
SDLFLAGS := `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf 
COMPILE := $(CC) $(CFLAGS)
# OBJS := Game.o Texture.o Entity.o Maze.o Graph.o Player.o Wall.o Collision.o Drone.o Automated.o Monster.o Stone.o Remote.o

OBJS := Game.o Texture.o Entity.o Maze.o Graph.o Player.o Wall.o Collision.o Drone.o Automated.o Monster.o Stone.o Snitch.o Health.o Broom.o Button.o Spell.o Remote.o


all: $(OBJS) main.o
	$(COMPILE) -o game $(OBJS) main.o $(SDLFLAGS)

Button.o : Game.hpp Button.hpp Button.cpp Texture.hpp
	$(COMPILE) -c Button.cpp $(SDLFLAGS)

Health.o : Game.hpp Entity.hpp Health.hpp Health.cpp
	$(COMPILE) -c Health.cpp $(SDLFLAGS)

Spell.o : Game.hpp Entity.hpp Spell.hpp Spell.cpp
	$(COMPILE) -c Spell.cpp $(SDLFLAGS)

Wall.o : Wall.cpp Wall.hpp Entity.hpp includes.hpp Game.hpp
	$(COMPILE) -c Wall.cpp $(SDLFLAGS)

Collision.o : Collision.cpp Collision.hpp includes.hpp Entity.hpp
	$(COMPILE) -c Collision.cpp $(SDLFLAGS)

Stone.o : Stone.cpp Stone.hpp Entity.hpp includes.hpp Game.hpp Texture.hpp
	$(COMPILE) -c Stone.cpp $(SDLFLAGS)

Monster.o : Monster.cpp Monster.hpp Entity.hpp includes.hpp Game.hpp Collision.hpp
	$(COMPILE) -c Monster.cpp $(SDLFLAGS)

Snitch.o : Snitch.cpp Snitch.hpp Entity.hpp includes.hpp Game.hpp Collision.hpp
	$(COMPILE) -c Snitch.cpp $(SDLFLAGS)

Automated.o : Automated.cpp Automated.hpp Entity.hpp includes.hpp Game.hpp
	$(COMPILE) -c Automated.cpp $(SDLFLAGS)

Drone.o : Drone.cpp Drone.hpp Entity.hpp includes.hpp Game.hpp Collision.hpp
	$(COMPILE) -c Drone.cpp $(SDLFLAGS)

Broom.o : includes.hpp Collision.hpp Game.hpp Entity.hpp Broom.hpp Broom.cpp Player.hpp
	$(COMPILE) -c Broom.cpp $(SDLFLAGS)
	
Remote.o : Remote.cpp Player.hpp Entity.hpp includes.hpp Game.hpp Collision.hpp
	$(COMPILE) -c Remote.cpp $(SDLFLAGS)

Player.o : Player.cpp Player.hpp Entity.hpp includes.hpp Game.hpp Collision.hpp
	$(COMPILE) -c Player.cpp $(SDLFLAGS)

Graph.o : Graph.cpp Graph.hpp includes.hpp
	$(COMPILE) -c Graph.cpp $(SDLFLAGS)

Maze.o : Maze.cpp Texture.hpp Maze.hpp Graph.hpp includes.hpp Entities.hpp Game.hpp Wall.hpp
	$(COMPILE) -c Maze.cpp $(SDLFLAGS)

Entity.o : Entity.cpp Game.hpp Texture.hpp Entity.hpp includes.hpp
	$(COMPILE) -c Entity.cpp $(SDLFLAGS)

Texture.o : Texture.cpp Game.hpp Texture.hpp includes.hpp
	$(COMPILE) -c Texture.cpp $(SDLFLAGS)

main.o : main.cpp Game.hpp includes.hpp Texture.hpp Button.hpp helpers.hpp sockets.hpp
	$(COMPILE) -c main.cpp $(SDLFLAGS)

server.o : server.cpp Game.hpp includes.hpp
	$(COMPILE) -c server.cpp $(SDLFLAGS)

client.o : client.cpp Game.hpp includes.hpp
	$(COMPILE) -c client.cpp $(SDLFLAGS)

Game.o : Game.cpp Maze.hpp Entity.hpp Texture.hpp Game.hpp Entities.hpp Entity.hpp Player.hpp includes.hpp
	$(COMPILE) -c Game.cpp $(SDLFLAGS)

run:
	./game

clean:
	rm *.o
	rm game