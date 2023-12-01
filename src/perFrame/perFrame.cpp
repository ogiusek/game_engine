#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <functional>

using namespace std;

bool PerFrame(PerFrameProps *props, Object *mainObject)
{
  bool show_performance = false;
  int preformanceTimer = SDL_GetTicks();

  // inputs->coutAll();
  if (!GetInput(props->inputs) || props->inputs->isHeld(SDLK_ESCAPE))
    return 1;

  if (props->inputs->isPressed(SDLK_F11))
    ToggleFullScreen(props->window);

  if (show_performance)
  {
    cout << "input " << SDL_GetTicks() - preformanceTimer << "ms ";
    preformanceTimer = SDL_GetTicks();
  }

  // update
  mainObject->Update(props);

  if (show_performance)
  {
    cout << "update " << SDL_GetTicks() - preformanceTimer << "ms ";
    preformanceTimer = SDL_GetTicks();
  }

  // draw
  auto DrawBackgroundLambda = [](Window *window) -> void
  {
    SDL_Rect rect = {0, 0, window->width, window->height};
    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(window->renderer, &rect);
  };

  auto DrawLambda = [&mainObject, &props](Window *window) -> void
  { mainObject->Draw(props); };

  Draw(props, {DrawBackgroundLambda, DrawLambda});

  if (show_performance)
  {
    cout << "draw " << SDL_GetTicks() - preformanceTimer << "ms\n";
    preformanceTimer = SDL_GetTicks();
  }

  // end
  return 0;
}
