#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

using namespace std;

void DrawText(Window *window, int x, int y, string text, int fontSize = 32, SDL_Color color = {0, 0, 0})
{

  TTF_Font *font = TTF_OpenFont("assets/fonts/font.ttf", fontSize);
  if (font == NULL)
  {
    cout << "Font do not loaded\n";
    return;
  }

  SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);

  SDL_Texture *texture = SDL_CreateTextureFromSurface(window->renderer, surface);

  SDL_Rect destRect = {x, y, surface->w, surface->h};
  SDL_RenderCopy(window->renderer, texture, NULL, &destRect);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  TTF_CloseFont(font);
}
