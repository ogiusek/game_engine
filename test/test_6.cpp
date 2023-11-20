#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <map>
#include <string>

using namespace std;

class Textures
{
private:
  map<const char *, SDL_Surface *> surfaces;

public:
  SDL_Texture *get(SDL_Renderer *renderer, const string path)
  { // how draw
    // SDL_RenderCopy(props.window->renderer, texture, NULL, NULL);
    // SDL_RenderCopy(props.window->renderer, texture, (pos on image rect), (image pos rect));
    const char *key = path.c_str();
    if (!surfaces.count(key))
      surfaces[key] = IMG_Load(key);
    return SDL_CreateTextureFromSurface(renderer, surfaces[key]);
  }
};

int main()
{
  Textures textures;
  // SDL Init
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("SDL2 Displaying Image",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        640, 480, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

  // Actual test
  //  Load image
  const char *str = "image.jpg";
  string sss = str;
  SDL_Surface *imageSurface = IMG_Load("image.jpg");
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
  SDL_FreeSurface(imageSurface);

  //  Render texture
  SDL_RenderClear(renderer);
  for (int i = 0; i < 10; i++)
  {
    textures.get(renderer, "image.jpg");
  }
  SDL_RenderCopy(renderer, textures.get(renderer, "image.jpg"), NULL, NULL);
  // SDL_RenderCopy(renderer, texture, NULL, NULL);

  // Test end
  SDL_RenderPresent(renderer);

  SDL_Delay(1000);

  // SDL Cleanup
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
  // SDL_Surface *imageSurface = IMG_Load("image.jpg");
  // SDL_Texture *texture = SDL_CreateTextureFromSurface(props.window->renderer, imageSurface);
  // SDL_FreeSurface(imageSurface);

  // // SDL_RenderCopy(props.window->renderer, texture, NULL, NULL);
  // SDL_Rect rect = {50, 50, 100, 100};
  // SDL_RenderCopy(props.window->renderer, texture, &rect, NULL);
  // return 0;
}
