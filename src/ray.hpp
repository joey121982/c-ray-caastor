#ifndef RAY_HPP
#define RAY_HPP

#include "controls.hpp"
#include "map.hpp"
#include "player.hpp"
#include "settings.hpp"
#include "utilities.hpp"

class Ray {
 public:
  float rayAngle;
  Player* player;
  Map* map;
  Controls* controls;
  bool is_facing_down;
  bool is_facing_up;
  bool is_facing_right;
  bool is_facing_left;
  float wall_hit_x;
  float wall_hit_y;
  float distance;
  int color;

 public:
  Ray(float g_rayAngle, Player* g_player, Map* g_map, Controls* g_controls) {
    rayAngle = normalizeAngle(g_rayAngle);
    player = g_player;
    map = g_map;
    controls = g_controls;
    is_facing_down = rayAngle > 0 && rayAngle < M_PI;
    is_facing_up = !is_facing_down;
    is_facing_right = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
    is_facing_left = !is_facing_right;
    wall_hit_x = 0;
    wall_hit_y = 0;
    distance = 0;
    color = 255;
  }

  /// @brief finding ray length
  void cast() {
    // horizontal check
    bool found_horizontal_wall = false;
    float horizontal_hit_x = 0;
    float horizontal_hit_y = 0;
    float first_intersection_x = 0;
    float first_intersection_y = 0;

    if (is_facing_up) {
      first_intersection_y = int(player->y / TILESIZE) * TILESIZE - 0.01;
    } else {
      first_intersection_y = int(player->y / TILESIZE) * TILESIZE + TILESIZE;
    }
    first_intersection_x = player->x + (first_intersection_y - player->y) / tan(rayAngle);

    float next_horizontal_x = first_intersection_x;
    float next_horizontal_y = first_intersection_y;
    // adjustments for each iteration
    float xa = 0, ya = 0;
    if (is_facing_up)
      ya = -TILESIZE;
    else
      ya = TILESIZE;
    xa = ya / tan(rayAngle);

    while (next_horizontal_x <= WINDOW_WIDTH && next_horizontal_x >= 0 && next_horizontal_y <= WINDOW_HEIGHT && next_horizontal_y >= 0) {
      if (map->has_wall_at(next_horizontal_x, next_horizontal_y)) {
        found_horizontal_wall = true;
        horizontal_hit_x = next_horizontal_x;
        horizontal_hit_y = next_horizontal_y;
        break;
      } else {
        next_horizontal_x += xa;
        next_horizontal_y += ya;
      }
    }

    // vertical check
    bool found_vertical_wall = false;
    float vertical_hit_x = 0;
    float vertical_hit_y = 0;

    if (is_facing_right) {
      first_intersection_x = int(player->x / TILESIZE) * TILESIZE + TILESIZE;
    } else {
      first_intersection_x = int(player->x / TILESIZE) * TILESIZE - 0.01;
    }

    first_intersection_y = player->y + (first_intersection_x - player->x) * tan(rayAngle);

    float next_vertical_x = first_intersection_x;
    float next_vertical_y = first_intersection_y;
    // adjustments for each iteration
    if (is_facing_right)
      xa = TILESIZE;
    else
      xa = -TILESIZE;
    ya = xa * tan(rayAngle);

    while (next_vertical_x <= WINDOW_WIDTH && next_vertical_x >= 0 && next_vertical_y <= WINDOW_HEIGHT && next_vertical_y >= 0) {
      if (map->has_wall_at(next_vertical_x, next_vertical_y)) {
        found_vertical_wall = true;
        vertical_hit_x = next_vertical_x;
        vertical_hit_y = next_vertical_y;
        break;
      } else {
        next_vertical_x += xa;
        next_vertical_y += ya;
      }
    }

    // distance calculation, finding wall hit coordinates
    float horizontal_distance = 0;
    float vertical_distance = 0;
    if (found_horizontal_wall) {
      horizontal_distance = distance_between(player->x, player->y, horizontal_hit_x, horizontal_hit_y);
    } else {
      horizontal_distance = 99999;
    }

    if (found_vertical_wall) {
      vertical_distance = distance_between(player->x, player->y, vertical_hit_x, vertical_hit_y);
    } else {
      vertical_distance = 99999;
    }

    if (horizontal_distance < vertical_distance) {
      wall_hit_x = horizontal_hit_x;
      wall_hit_y = horizontal_hit_y;
      distance = horizontal_distance;
      color = 160;
    } else {
      wall_hit_x = vertical_hit_x;
      wall_hit_y = vertical_hit_y;
      distance = vertical_distance;
      color = 255;
    }

    if (!controls->fish_eye_effect) {
      distance *= cos(player->rotationAngle - rayAngle);
    }

    if (controls->shading_effect) {
      color *= (controls->shading_distance / distance);
      if (color > 255)
        color = 255;
      if (color < 0)
        color = 0;
    }
  }

  /// @brief render ray for map mode
  void render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, player->x, player->y, wall_hit_x, wall_hit_y);
  }
};

#endif  // guard