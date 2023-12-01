#include <SDL2/SDL.h>
#include <vector>

#include <iostream>
using namespace std;

int GetInput(Inputs *inputs)
{
  SDL_Event event;
  int running = 1;

  inputs->clearPressed();

  int newMouseX, newMouseY;
  SDL_GetMouseState(&newMouseX, &newMouseY);
  inputs->mouse.setXY(newMouseX, newMouseY);

  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
      running = 0;

    int pressed_key = int(event.key.keysym.sym);
    int pressed_btn = int(event.button.button);

    if (event.type == SDL_MOUSEWHEEL)
      inputs->mouse.scroll = event.wheel.y;

    if (event.type == SDL_MOUSEBUTTONDOWN)
      inputs->mouse.addHeld(pressed_btn);

    if (event.type == SDL_MOUSEBUTTONUP)
    {
      inputs->mouse.addPressed(pressed_btn);
      inputs->mouse.removeHeld(pressed_btn);
    }

    if (event.type == SDL_KEYDOWN)
      inputs->addHeld(pressed_key);

    if (event.type == SDL_KEYUP)
    {
      inputs->addPressed(pressed_key);
      inputs->removeHeld(pressed_key);
    }
  }

  return running;
}