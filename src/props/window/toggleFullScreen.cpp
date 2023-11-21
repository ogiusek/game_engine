#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

using namespace std;

void ToggleFullScreen(Window *window)
{
  Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN;
  bool isFullscreen = SDL_GetWindowFlags(window->window) & fullscreenFlag;
  SDL_SetWindowFullscreen(window->window, isFullscreen ? 0 : fullscreenFlag);
}
