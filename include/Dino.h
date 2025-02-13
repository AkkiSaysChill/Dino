#ifndef DINO_H
#define DINO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Dino {
public:
    Dino();
    ~Dino();

    bool init(SDL_Renderer* renderer, const char* imagePath, int x, int y);
    void update(double deltaTime, int groundLevel);
    void render(SDL_Renderer* renderer);
    void jump();
    SDL_Rect getCollisionRect() const;

private:
    SDL_Texture* texture;
    SDL_Rect rect;  // Position and size
    double yVelocity;
    bool isJumping;
    const double JUMP_STRENGTH = -600.0; // Negative for upward movement.
    const double GRAVITY = 1800.0;
};

#endif
