#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>
#include <cmath>
#include "settings.hpp"
#include "utilities.hpp"

class Player {
 public:
  float x = WINDOW_WIDTH / 2;
  float y = WINDOW_HEIGHT / 2;
  int radius = 3;
  int turnDirection = 0;
  int walkDirection = 0;
  float rotationAngle = 270 * (M_PI / 180);
  float rotationSpeed = 2 * (M_PI / 180);
  float moveSpeed = 2.5;

 public:
  Player() {};
  void update() {
    turnDirection = 0;
    walkDirection = 0;
    const uint8_t* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) {
      turnDirection = 1;
    }
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) {
      turnDirection = -1;
    }
    if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) {
      walkDirection = 1;
    }
    if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) {
      walkDirection = -1;
    }
    float moveStep = walkDirection * moveSpeed;
    rotationAngle += turnDirection * rotationSpeed;
    x += cos(rotationAngle) * moveStep;
    y += sin(rotationAngle) * moveStep;
  }
  void render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    DrawCircle(renderer, x, y, radius);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawLine(renderer, x, y, x + cos(rotationAngle) * 50, y + sin(rotationAngle) * 50);
  }
};

#endif  // guard