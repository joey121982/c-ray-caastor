#ifndef RAYCASTER_HPP
#define RAYCASTER_HPP

#include <vector>
#include "controls.hpp"
#include "map.hpp"
#include "player.hpp"
#include "ray.hpp"
#include "settings.hpp"

class Raycaster {
 private:
  std::vector<Ray> rays;
  Player* player;
  Map* map;
  Controls* controls;

 public:
  Raycaster() {}

  Raycaster(Player* g_player, Map* g_map, Controls* g_controls) {
    rays = {};
    player = g_player;
    map = g_map;
    controls = g_controls;
  }

  void castAllRays() {
    rays = {};
    float rayAngle = player->rotationAngle - FOV / 2;
    for (int i = 0; i < NUM_RAYS; i++) {
      Ray ray = Ray(rayAngle, player, map, controls);
      ray.cast();
      rays.push_back(ray);
      rayAngle += FOV / NUM_RAYS;
    }
  }

  void render(SDL_Renderer* renderer, SDL_Surface* background) {
    if (!controls->map_mode) {
      SDL_Texture* background_texture = SDL_CreateTextureFromSurface(renderer, background);
      SDL_RenderCopy(renderer, background_texture, NULL, NULL);
      SDL_DestroyTexture(background_texture);
    }

    for (int i = 0; i < rays.size(); i++) {
      float line_height = (TILESIZE / rays[i].distance) * 415;
      float draw_begin = WINDOW_HEIGHT / 2 - line_height / 2;
      float draw_end = line_height;
      if (controls->map_mode) {
        rays[i].render(renderer);
      } else {
        SDL_SetRenderDrawColor(renderer, rays[i].color, rays[i].color, rays[i].color, 255);
        SDL_Rect rayRect = {i * RES, draw_begin, RES, draw_end};
        SDL_RenderDrawRect(renderer, &rayRect);
      }
    }
  }
};

#endif  // guard