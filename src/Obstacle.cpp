#include "Obstacle.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Obstacle::Obstacle() : texture(nullptr), speed(0) {
    rect = {0, 0, 50, 50};  // Default size (you can change this)
}

Obstacle::~Obstacle() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

bool Obstacle::init(SDL_Renderer* renderer, SDL_Texture* tex, int x, int y) {
    texture = tex;
    rect.x = x;
    rect.y = y - rect.h;  // Position the obstacle on the ground

    return texture != nullptr;
}

void Obstacle::update(double deltaTime, double speed) {
    rect.x -= speed * deltaTime;  // Move the obstacle
}

void Obstacle::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

bool Obstacle::isOffScreen() const {
    return rect.x + rect.w < 0;
}

SDL_Rect Obstacle::getCollisionRect() const {
    return rect;
}

