#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <map>
#include <string>

using namespace std;

class Textures
{
private:
  map<string, SDL_Surface *> surfaces;

public:
  SDL_Texture *get(SDL_Renderer *renderer, string path)
  {
    string key = path;
    if (!surfaces.count(key))
      surfaces[key] = IMG_Load(key.c_str());
    return SDL_CreateTextureFromSurface(renderer, surfaces[key]);
  }

  void Draw(SDL_Renderer *renderer, string path, SDL_Rect *srcrect = NULL, SDL_Rect *dstrect = NULL)
  {
    SDL_Texture *texture = get(renderer, path);
    SDL_RenderCopy(renderer, texture, srcrect, dstrect);
    SDL_DestroyTexture(texture);
  }
};