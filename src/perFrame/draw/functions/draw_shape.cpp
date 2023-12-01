#include <iostream>
#include <SDL2/SDL.h>

#include <vector>

using namespace std;

void Draw_shape(SDL_Renderer *renderer, vector<SDL_Vertex> vertexes)
{
  if (vertexes.size() > 3)
    vertexes.push_back(vertexes[0]);
  while (vertexes.size() > 2)
  {
    SDL_Vertex vertexesToDraw[3] = {vertexes[0], vertexes[1], vertexes[2]};
    SDL_RenderGeometry(renderer, NULL, vertexesToDraw, 3, NULL, 0);
    vertexes.erase(vertexes.begin());
  }
}
// SDL_Color color = {0, 0, 255, 255};
// vector<SDL_Vertex> vertexes = {{{50, 50}, color},
//                                {{100, 50}, color},
//                                {{150, 100}, color},
//                                {{50, 100}, color}};

// Draw_shape(props->window->renderer, vertexes);