#ifndef MAP_HPP
#define MAP_HPP

#include <SDL2/SDL.h>
#include "settings.hpp"
#include "utilities.hpp"

class Map {
 private:
  bool grid[10][15] = {
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
      {1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
      {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
      {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

 public:
  bool has_wall_at(int x, int y) {
    return grid[int(y / TILESIZE)][int(x / TILESIZE)] != 0;
  }

  void render(SDL_Renderer* renderer) {
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 15; j++) {
        auto tile_x = j * TILESIZE;
        auto tile_y = i * TILESIZE;
        Color color;
        if (grid[i][j] == 0) {
          color = Color(255, 255, 255);
        } else {
          color = Color(0, 0, 0);
        }
        SDL_Rect tileRect = {tile_x, tile_y, TILESIZE - 1, TILESIZE - 1};
        SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, 255);
        SDL_RenderFillRect(renderer, &tileRect);
      }
    }
  }
};

#endif  // guard