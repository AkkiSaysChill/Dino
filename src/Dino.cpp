#include "Dino.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Dino::Dino() : texture(nullptr), yVelocity(0), isJumping(false) {
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;  // Initialize width and height
    rect.h = 0;
}
Dino::~Dino() {
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

bool Dino::init(SDL_Renderer* renderer, const char* imagePath, int x, int y)
{
    rect.x = x;
    rect.y = y;


     //Load image
    SDL_Surface* loadedSurface = IMG_Load(imagePath);
    if (!loadedSurface)
    {
        std::cerr << "Unable to load image " << imagePath << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }
    else{

        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (!texture)
        {
            std::cerr << "Unable to create texture from " << imagePath << "! SDL Error: " << SDL_GetError() << std::endl;
              SDL_FreeSurface(loadedSurface);
            return false;
        }
         //Get image dimensions
        rect.w = loadedSurface->w;
        rect.h = loadedSurface->h;

         //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return true;
}

void Dino::update(double deltaTime, int groundLevel) {
    if (isJumping) {
        yVelocity += GRAVITY * deltaTime; // Apply gravity
        rect.y += static_cast<int>(yVelocity * deltaTime);

        if (rect.y >= groundLevel - rect.h) { // Check for ground collision
            rect.y = groundLevel - rect.h;  // Reset position to ground
            yVelocity = 0.0;
            isJumping = false;
        }
    }
}
void Dino::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Dino::jump() {
    if (!isJumping) {
        yVelocity = JUMP_STRENGTH;
        isJumping = true;
    }
}
SDL_Rect Dino::getCollisionRect() const {
    return rect;
}
