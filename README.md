# Harry Potter and the Deathly Hallows
A 2-player C++ maze game and simulation for COP290.  
## Dependencies
* SDL for C++  

## Installation
Ubuntu - 
```bash
#install sdl2
sudo apt install libsdl2-dev libsdl2-2.0-0 -y
#install sdl image
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y
#install sdl mixer
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y
#install sdl ttf
sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y
```
MacOS - 
```bash
#install sdl2
brew install sdl2
#install sdl image
brew install sdl2_image
#install sdl mixer
brew install sdl2_mixer
#install sdl ttf
brew install sdl2_ttf
```

## Build executable
```bash
cd ./Code
make
```
This builds the executable ./game
## Run
```bash
./game
```
Initially a menu will appear giving the choice of
* Single Player Game
* Multi Player Game
* Run Simulation  

and the character sprite (Harry/Ron/Hermione).

The game has 2 modes - 
1. **Single Player**
* The game objective is to collect all 3 objects - the Resurrection Stone (within the Snitch), Broom and Invisibilitiy Cloak.
* Dragons will try to prevent the user from collecting these items.
* The user can collect a Wand to shoot spells.
2. **Multi Player**
* Two players compete against each other in a death-match.
* Most of the game is similar to the Single Player version.

For the **Simulation** - 
* A drone's objective is to collect all the stones and reach the end of the maze.

## License
MIT
