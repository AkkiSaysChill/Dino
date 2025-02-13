#include "Game.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int SDL_main(int argc, char* argv[]) { // Rename main to SDL_main
    Game game;
    if (game.init()) {
        game.run();
    }
    return 0;
}

