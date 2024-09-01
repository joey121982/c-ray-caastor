#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>
#include <cmath>
#include "controls.hpp"
#include "settings.hpp"
#include "utilities.hpp"

class Player {
 public:
  float x = WINDOW_WIDTH / 2;
  float y = WINDOW_HEIGHT / 2;
  int radius = 3;
  int turnDirection = 0;
  int walkForwardDirection = 0;
  int walkSidewaysDirection = 0;
  int walkDirection = 0;
  float rotationAngle = 270 * (M_PI / 180);
  float rotationSpeed = 2 * (M_PI / 180);
  float mouseSensitivity = 0.001f;
  float moveSpeed = 2.5;
  Controls* controls;
  Map* map;

 public:
  Player() {};
  Player(Controls* g_controls, Map* g_map) {
    controls = g_controls;
    map = g_map;
  };

  void update() {
    turnDirection = 0;
    walkForwardDirection = 0;
    walkSidewaysDirection = 0;
    walkDirection = 0;
    const uint8_t* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_RIGHT]) {
      turnDirection = 1;
    }
    if (keys[SDL_SCANCODE_LEFT]) {
      turnDirection = -1;
    }
    if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) {
      walkForwardDirection = 1;
    }
    if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) {
      walkForwardDirection = -1;
    }
    if (keys[SDL_SCANCODE_A]) {
      walkSidewaysDirection = -1;
    }
    if (keys[SDL_SCANCODE_D]) {
      walkSidewaysDirection = 1;
    }

    if (controls->mouse_locked == SDL_TRUE) {
      int mouseX, mouseY;
      SDL_GetRelativeMouseState(&mouseX, &mouseY);
      rotationAngle += mouseX * mouseSensitivity;
    }
    rotationAngle += turnDirection * rotationSpeed;

    float next_x = x;
    float next_y = y;

    if (walkForwardDirection == 1 && walkSidewaysDirection == 1) {
      // Moving forward and to the right (diagonal up-right)
      next_x += cos(rotationAngle + M_PI_4) * moveSpeed;
      next_y += sin(rotationAngle + M_PI_4) * moveSpeed;
    } else if (walkForwardDirection == -1 && walkSidewaysDirection == 1) {
      // Moving backward and to the right (diagonal down-right)
      next_x -= cos(rotationAngle - M_PI_4) * moveSpeed;
      next_y -= sin(rotationAngle - M_PI_4) * moveSpeed;
    } else if (walkForwardDirection == 1 && walkSidewaysDirection == -1) {
      // Moving forward and to the left (diagonal up-left)
      next_x += cos(rotationAngle - M_PI_4) * moveSpeed;
      next_y += sin(rotationAngle - M_PI_4) * moveSpeed;
    } else if (walkForwardDirection == -1 && walkSidewaysDirection == -1) {
      // Moving backward and to the left (diagonal down-left)
      next_x -= cos(rotationAngle + M_PI_4) * moveSpeed;
      next_y -= sin(rotationAngle + M_PI_4) * moveSpeed;
    } else if (walkForwardDirection == 1) {
      // Moving straight forward
      next_x += cos(rotationAngle) * moveSpeed;
      next_y += sin(rotationAngle) * moveSpeed;
    } else if (walkForwardDirection == -1) {
      // Moving straight backward
      next_x += cos(rotationAngle + M_PI) * moveSpeed;
      next_y += sin(rotationAngle + M_PI) * moveSpeed;
    } else if (walkSidewaysDirection == 1) {
      // Moving to the right
      next_x += cos(rotationAngle + M_PI_2) * moveSpeed;
      next_y += sin(rotationAngle + M_PI_2) * moveSpeed;
    } else if (walkSidewaysDirection == -1) {
      // Moving to the left
      next_x += cos(rotationAngle - M_PI_2) * moveSpeed;
      next_y += sin(rotationAngle - M_PI_2) * moveSpeed;
    }

    if (!map->has_wall_at(next_x, next_y)) {
      x = next_x;
      y = next_y;
    }
  }
  void render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    DrawCircle(renderer, x, y, radius);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawLine(renderer, x, y, x + cos(rotationAngle) * 50, y + sin(rotationAngle) * 50);
  }
};

#endif  // guard