#include "Obstacle.h"
#include <SDL_image.h>
#include <iostream>

Obstacle::Obstacle(): texture(nullptr){
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}
Obstacle::~Obstacle() {
    SDL_DestroyTexture(texture);
    texture = nullptr;
}
bool Obstacle::init(SDL_Renderer* renderer, const char* imagePath, int x, int y)
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

void Obstacle::update(double deltaTime, double gameSpeed) {
    rect.x -= static_cast<int>(gameSpeed * deltaTime);
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
