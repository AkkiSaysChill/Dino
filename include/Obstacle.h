#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <SDL.h>

class Obstacle {
    public:
    Obstacle();
    ~Obstacle();
    bool init(SDL_Renderer* renderer, const char* imagePath, int x, int y); // Corrected
    void update(double deltaTime, double gameSpeed);
    void render(SDL_Renderer* renderer);
    bool isOffScreen() const;
    SDL_Rect getCollisionRect() const;

    private:
    SDL_Texture* texture;
    SDL_Rect rect;
};
#endif
