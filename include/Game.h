#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Dino.h"
#include "Obstacle.h"

class Game {
public:
    Game();
    ~Game();
    bool init();
    void run();
    void close();

private:
    bool handleInput();
    void update(double deltaTime);
    void render();
    void spawnObstacle();
    bool checkCollision();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    double score;
    double gameSpeed;
    Dino dino;
    std::vector<Obstacle> obstacles;

    // Cactus texture for obstacles
    SDL_Texture* cactusTexture;
};

#endif // GAME_H
