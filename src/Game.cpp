#include "Game.h"
#include <iostream>
#include <random>
#include <algorithm>  // For std::remove_if
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Constants (can be adjusted)
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const double INITIAL_GAME_SPEED = 200.0;
const double SPEED_INCREASE_RATE = 10.0;  // Increase speed over time
const double OBSTACLE_SPAWN_RATE = 1.5; // Seconds between spawns
const int GROUND_LEVEL = SCREEN_HEIGHT - 50;

Game::Game() : isRunning(false), window(nullptr), renderer(nullptr), score(0), gameSpeed(INITIAL_GAME_SPEED), cactusTexture(nullptr) {}

Game::~Game() {
    close();
}

bool Game::init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    window = SDL_CreateWindow("Dino Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Load cactus texture for obstacles
    cactusTexture = IMG_LoadTexture(renderer, "assets/cactus.png");
    if (cactusTexture == nullptr) {
        std::cerr << "Failed to load cactus texture! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Initialize Dino and other game elements
    if (!dino.init(renderer, "assets/dino.png", 100, GROUND_LEVEL)) {
        std::cerr << "Failed to initialize Dino!" << std::endl;
        return false;
    }

    return true;
}

void Game::run() {
    isRunning = true;
    double lastTime = SDL_GetTicks() / 1000.0; // Time in seconds
    double accumulator = 0.0;
    double obstacleTimer = 0.0;  // Timer for obstacle spawning

    while (isRunning) {
        double currentTime = SDL_GetTicks() / 1000.0;
        double frameTime = currentTime - lastTime;
        lastTime = currentTime;

        accumulator += frameTime;

        // Fixed timestep for updates
        const double deltaTime = 1.0 / 60.0;  // 60 FPS (Update at 60Hz)
        while (accumulator >= deltaTime) {
            handleInput();
            update(deltaTime);
            accumulator -= deltaTime;
            obstacleTimer += deltaTime;

            if (obstacleTimer >= OBSTACLE_SPAWN_RATE) {
                spawnObstacle();
                obstacleTimer = 0.0; // Reset timer.
            }
        }

        // Cap the frame rate to 60 FPS.
        int frameDelay = 1000 / 60; // Milliseconds per frame
        int frameTimeMillis = SDL_GetTicks() - currentTime;
        if (frameTimeMillis < frameDelay) {
            SDL_Delay(frameDelay - frameTimeMillis);
        }

        render(); // Render as fast as possible (or capped by VSync)
    }
}


bool Game::handleInput() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            isRunning = false;
            return true; // Return true if the input was handled
        }
        else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP) {
                dino.jump();
                return true; // Return true if input was handled
            }
        }
    }
    return false; // No input handled
}


void Game::update(double deltaTime) {
    dino.update(deltaTime, GROUND_LEVEL);
    // Update obstacles
    for (Obstacle& obs : obstacles) {
        obs.update(deltaTime, gameSpeed);
    }

    // Remove off-screen obstacles
    obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
        [](const Obstacle& o) { return o.isOffScreen(); }), obstacles.end());

    // Check for collisions
    if (checkCollision()) {
        // Game over logic here (for now, we will just stop the game)
        isRunning = false;
    }

    // Update score
    score += gameSpeed * deltaTime * 0.1; // Score increases with game speed and time

    // Increase game speed gradually
    gameSpeed += SPEED_INCREASE_RATE * deltaTime;
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(renderer);

    // Draw ground (simple line)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
    SDL_RenderDrawLine(renderer, 0, GROUND_LEVEL, SCREEN_WIDTH, GROUND_LEVEL);

    // Render dino
    dino.render(renderer);

    // Render obstacles
    for (Obstacle& obs : obstacles) {
        obs.render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::spawnObstacle() {
    // Create obstacle and use the cactus texture
    Obstacle newObstacle;
    if (!newObstacle.init(renderer, cactusTexture, SCREEN_WIDTH, GROUND_LEVEL)) {
        std::cerr << "Failed to initialize obstacle" << std::endl;
        return;
    }
    obstacles.push_back(newObstacle);
}

bool Game::checkCollision() {
    SDL_Rect dinoRect = dino.getCollisionRect();

    for (const Obstacle& obs : obstacles) {
        SDL_Rect obsRect = obs.getCollisionRect();
        if (SDL_HasIntersection(&dinoRect, &obsRect)) {
            return true; // Collision detected
        }
    }
    return false; // No collision
}

void Game::close() {
    // Destroy window and renderer
    SDL_DestroyTexture(cactusTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
