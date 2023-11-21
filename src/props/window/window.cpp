#include <SDL2/SDL.h>
using namespace std;

class Window
{
public:
  int width, height,
      &w = width, &h = height;

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  Window(int _width, int _height) : width(_width), height(_height) {}
};

Window INIT_WINDOW(int width, int height)
{
  Window window(width, height);

  TTF_Init();

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    cout << "ERROR " << SDL_GetError();
    throw "SDL could not initialize!";
  }

  // Create a window
  window.window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  if (window.window == NULL)
  {
    cout << "ERROR " << SDL_GetError();
    throw "Window could not be created!";
  }

  // Create a renderer
  window.renderer = SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED);
  if (window.renderer == NULL)
  {
    cout << "ERROR " << SDL_GetError();
    throw "Renderer could not be created!";
  }

  return window;
}

void CLOSE_WINDOW(Window *window)
{
  TTF_Quit();
  SDL_DestroyRenderer(window->renderer);
  SDL_DestroyWindow(window->window);
  SDL_Quit();
}