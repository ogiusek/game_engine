#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include <functional>

#include <thread>
#include <cmath>
#include <string>

#include <cstdlib>
#include <ctime>

using namespace std;

#include "include.h"

int main()
{

  srand(time(0));
  Window window = INIT_WINDOW(1280, 720);
  Inputs inputs;

  FPS fps(60);

  PerFrameProps props(&window, &fps, &inputs);

  auto perFrame = [&props]() -> bool
  { return PerFrame(&props, mainObject); };

  perFrame();

  int running = 1;
  UserMain();
  while (running)
  {
    fps.MakeNewFrame();

    if (perFrame())
      break;
  }

  CLOSE_WINDOW(&window);

  return 0;
}