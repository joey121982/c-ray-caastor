#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <cmath>

const int TILESIZE = 64;
const int ROWS = 10;
const int COLS = 15;

const int WINDOW_WIDTH = COLS * TILESIZE;
const int WINDOW_HEIGHT = ROWS * TILESIZE;
const bool FULLSCREEN = false;

const float FOV = 60 * (M_PI / 180);
const float RES = 1000 / 1000;
const int NUM_RAYS = int(WINDOW_WIDTH / RES);

const bool FISH_EYE_EFFECT = false;
const bool SHADING_EFFECT = true;
const bool MAP_MODE = false;
const int SHADING_DISTANCE = 60;

#endif  // guard