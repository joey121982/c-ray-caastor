#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include "settings.hpp"

class Controls {
 public:
  SDL_bool mouse_locked = SDL_TRUE;
  bool fish_eye_effect = FISH_EYE_EFFECT;
  bool shading_effect = SHADING_EFFECT;
  int shading_distance = SHADING_DISTANCE;
  bool map_mode = MAP_MODE;

  void update(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
        case SDLK_F1:
          fish_eye_effect = !fish_eye_effect;
          break;
        case SDLK_F2:
          shading_effect = !shading_effect;
          break;
        case SDLK_F3:
          map_mode = !map_mode;
          break;
        case SDLK_PAGEUP:
          shading_distance += 10;
          break;
        case SDLK_PAGEDOWN:
          shading_distance -= 10;
          break;
        case SDLK_ESCAPE:
          if (mouse_locked == SDL_TRUE)
            mouse_locked = SDL_FALSE;
          else
            mouse_locked = SDL_TRUE;
          SDL_SetRelativeMouseMode(mouse_locked);
          break;
      }
    }
  }
};

#endif  // guard