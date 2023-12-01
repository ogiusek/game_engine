#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <functional>

using namespace std;

void Draw(PerFrameProps *props, vector<function<void(Window *)>> toDraw)
{
  // Clear the screen
  SDL_SetRenderDrawColor(props->window->renderer, 0, 0, 0, 255);
  SDL_RenderClear(props->window->renderer);

  for (auto method : toDraw)
    method(props->window);

  DrawText(props->window, 0, 0, (to_string(props->fps->fps_in_last_second) + "FPS"));
  // Draw::Text(gameState, 0, 0, (to_string(gameState->frames.fps) + "FPS"));
  // // Draw a rectangle
  // SDL_Rect rect = {100, 100, 200, 200};
  // SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
  // SDL_RenderFillRect(window->renderer, &rect);

  // Update the screen
  SDL_RenderPresent(props->window->renderer);
}