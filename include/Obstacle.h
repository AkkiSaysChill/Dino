#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Obstacle {
public:
    Obstacle();
    ~Obstacle();

    bool init(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);
    void update(double deltaTime, double speed);
    void render(SDL_Renderer* renderer);
    bool isOffScreen() const;
    SDL_Rect getCollisionRect() const;

private:
    SDL_Texture* texture;
    SDL_Rect rect;
    double speed;
};

#endif // OBSTACLE_H
