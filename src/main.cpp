#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "controls.hpp"
#include "map.hpp"
#include "player.hpp"
#include "raycaster.hpp"
#include "settings.hpp"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* background;
Map map;
Player player;
Controls controls;
Raycaster raycaster;
bool isRunning = true;

void initialize() {
  SDL_Init(SDL_INIT_EVERYTHING);

  window = SDL_CreateWindow("Caastor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, FULLSCREEN);
  renderer = SDL_CreateRenderer(window, -1, 0);

  background = IMG_Load("assets/background.png");
  if (!background) {
    std::cerr << "Failed to load background image: " << IMG_GetError() << std::endl;
  }

  SDL_SetRelativeMouseMode(SDL_TRUE);

  map = Map();
  controls = Controls();
  player = Player(&controls, &map);
  raycaster = Raycaster(&player, &map, &controls);
}

void update() {
  player.update();
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      isRunning = false;
    } else {
      controls.update(event);
    }
  }
}

void render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  raycaster.castAllRays();
  if (controls.map_mode) {
    map.render(renderer);
    raycaster.render(renderer, background);
    player.render(renderer);
  } else {
    raycaster.render(renderer, background);
  }
  SDL_RenderPresent(renderer);
}

void clear() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_FreeSurface(background);
  SDL_Quit();
}

int main() {
  initialize();
  while (isRunning == true) {
    SDL_Delay(8);
    update();
    render();
  }
  clear();
}