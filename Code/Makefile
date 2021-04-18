CC := g++
CFLAGS := -std=c++11 -w
SDLFLAGS := `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
COMPILE := $(CC) $(CFLAGS) $(WARNINGS) $(SDLFLAGS)

all: Game.o Texture.o Entity.o Maze.o Graph.o Player.o Wall.o Collision.o Drone.o Automated.o Monster.o main.o
	$(COMPILE) -o game Game.o Texture.o Entity.o Maze.o Graph.o Player.o Wall.o Collision.o Drone.o Automated.o Monster.o main.o
	./game

Wall.o : Wall.cpp Wall.hpp Entity.hpp includes.hpp Game.hpp
	$(COMPILE) -c Wall.cpp

Collision.o : Collision.cpp Collision.hpp includes.hpp
	$(COMPILE) -c Collision.cpp

Monster.o : Monster.cpp Monster.hpp Entity.hpp includes.hpp Game.hpp Collision.hpp
	$(COMPILE) -c Monster.cpp

Automated.o : Automated.cpp Automated.hpp Entity.hpp includes.hpp Game.hpp
	$(COMPILE) -c Automated.cpp

Drone.o : Drone.cpp Drone.hpp Entity.hpp includes.hpp Game.hpp Collision.hpp
	$(COMPILE) -c Drone.cpp

Player.o : Player.cpp Player.hpp Entity.hpp includes.hpp Game.hpp Collision.hpp
	$(COMPILE) -c Player.cpp

Graph.o : Graph.cpp Graph.hpp includes.hpp
	$(COMPILE) -c Graph.cpp

Maze.o : Maze.cpp Texture.hpp Maze.hpp Graph.hpp includes.hpp Entities.hpp Game.hpp Wall.hpp
	$(COMPILE) -c Maze.cpp

Entity.o : Entity.cpp Game.hpp Texture.hpp Entity.hpp includes.hpp
	$(COMPILE) -c Entity.cpp

Texture.o : Texture.cpp Game.hpp Texture.hpp includes.hpp
	$(COMPILE) -c Texture.cpp

main.o : main.cpp Game.hpp includes.hpp
	$(COMPILE) -c main.cpp

Game.o : Game.cpp Maze.hpp Entity.hpp Texture.hpp Game.hpp Entities.hpp Entity.hpp Player.hpp includes.hpp
	$(COMPILE) -c Game.cpp

run:
	./game

clean:
	rm *.o
	rm game