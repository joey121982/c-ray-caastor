#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <cmath>

/// @brief Color class with 3 members: R, G, B values
class Color {
 public:
  int R;
  int G;
  int B;

  Color() {
    R = 0;
    G = 0;
    B = 0;
  }

  Color(int r, int g, int b) {
    R = r;
    G = g;
    B = b;
  }
};

/// @brief Function to draw a circle to an SDL_Renderer
/// @param renderer SDL_Renderer
/// @param centreX X coord of centre of circle
/// @param centreY Y coord of centre of circle
/// @param radius Radius of circle
void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius) {
  const int32_t diameter = (radius * 2);

  int32_t x = (radius - 1);
  int32_t y = 0;
  int32_t tx = 1;
  int32_t ty = 1;
  int32_t error = (tx - diameter);

  while (x >= y) {
    //  Each of the following renders an octant of the circle
    SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
    SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
    SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
    SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
    SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
    SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
    SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
    SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

    if (error <= 0) {
      ++y;
      error += ty;
      ty += 2;
    }

    if (error > 0) {
      --x;
      tx += 2;
      error += (tx - diameter);
    }
  }
}

float normalizeAngle(float angle) {
  angle = std::fmod(angle, 2 * M_PI);
  if (angle <= 0)
    angle += 2 * M_PI;
  return angle;
}

float distance_between(float x1, float y1, float x2, float y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

#endif  // guard