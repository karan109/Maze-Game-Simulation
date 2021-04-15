CC := g++
CFLAGS := -std=c++14 -w
SDLFLAGS := `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
COMPILE := $(CC) $(CFLAGS) $(WARNINGS) $(SDLFLAGS)
# -lSDL2_net

all: Game.o Texture.o Entity.o Maze.o Graph.o main.o
	$(COMPILE) -o game Game.o Texture.o Entity.o Maze.o Graph.o main.o
	./game

Graph.o : Graph.cpp Graph.hpp
	$(COMPILE) -c Graph.cpp

Maze.o : Maze.cpp Texture.hpp Maze.hpp Graph.hpp
	$(COMPILE) -c Maze.cpp

Entity.o : Entity.cpp Game.hpp Texture.hpp Entity.hpp
	$(COMPILE) -c Entity.cpp

Texture.o : Texture.cpp Game.hpp Texture.hpp
	$(COMPILE) -c Texture.cpp

main.o : main.cpp Game.hpp
	$(COMPILE) -c main.cpp

Game.o : Game.cpp Maze.hpp Entity.hpp Texture.hpp Game.hpp
	$(COMPILE) -c Game.cpp

run:
	./game

clean:
	rm *.o
	rm game