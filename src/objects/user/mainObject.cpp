#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <functional>
#include <thread>
#include <cmath>

using namespace std;

class DrawBackgroundClass : public ScriptBase
{
public:
  void Update(Object *object, PerFrameProps *props) override {}

  void Draw(Object *object, PerFrameProps *props) override
  {
    // SDL_Rect rect = {50, 50, 100, 100};
    props->textures->Draw(props->window->renderer, "assets/img/image.jpg", NULL, NULL);
    SDL_SetRenderDrawColor(props->window->renderer, 255, 0, 0, 255);
  }

  DrawBackgroundClass(ScriptBase sb) : ScriptBase(sb) {}
};

class DrawWaveFunctionCollapse : public ScriptBase
{
private:
  WaveFunctionCollapse *defaultValue = nullptr;

public:
  void Update(Object *object, PerFrameProps *props) override {}
  void Draw(Object *object, PerFrameProps *props) override
  {
    if (defaultValue == nullptr)
    {
      vector<WFCTile> availableTiles = {
          {1, 1, {{1, 5}, {2}}},
          {2, 1, {{1}, {2, 5}, {3}}},
          {3, 1, {{2}, {3, 5}}},
      };
      int t = time(0);
      int size = 50;
      // for (int i = 1; i < 9; i++)
      // {
      //   WaveFunctionCollapse(availableTiles, size * i, size * i, t, 1);
      //   cout << endl;
      // }
      int sssize = 50;
      defaultValue = new WaveFunctionCollapse(availableTiles, sssize, sssize, t, 1);
      // for (int x = 0; x < sssize; x++)
      // {
      //   cout << "   ";
      //   for (int y = 0; y < sssize; y++)
      //     cout << defaultValue->get()[x][y].id << " ";
      //   cout << endl;
      // }
    }
    WaveFunctionCollapse *mapObject = object->get((defaultValue), 1);
    vector<vector<WFCTile>> map = mapObject->get();
    int tileSize = 15;
    for (int x = 0; x < map.size(); x++)
      for (int y = 0; y < map[x].size(); y++)
      {
        SDL_SetRenderDrawColor(props->window->renderer,
                               255 * (map[x][y].id == 1),
                               255 * (map[x][y].id == 2),
                               255 * (map[x][y].id == 3), 255);
        SDL_Rect rect = {y * tileSize, x * tileSize, tileSize, tileSize};
        SDL_Rect screen = {0, 0, props->window->w, props->window->h};
        if (SDL_HasIntersection(&rect, &screen))
          SDL_RenderFillRect(props->window->renderer, &rect);
        else
          break;
      }
  }
  // DrawWaveFunctionCollapse(ScriptBase sb) : ScriptBase(sb) {}
};

void UserMain()
{

  mainObject->set(Transform2D());
  mainObject->scripts.push_back(new DrawBackgroundClass(-1));

  VectorTree vt = mainObject->get<VectorTree>(VectorTree(mainObject));
  // vt.addChild(new Object({}, {new DrawWaveFunctionCollapse(1)}));
  vt.addChild(new Object({}, {new DrawWaveFunctionCollapse()}));
  // vt.addChild(new Object({Transform2D(0, 0, 50)}, {new DrawCircleClass({})}));

  // vt.addChild(new Object({Transform2D(50, 50, 100)}, {new DrawCircleClass({})}));
  // vt.addChild(new Object({Transform2D(150, 50, 100)}, {new DrawCircleClass({})}));
  // vt.addChild(new Object({Transform2D(250, 50, 100)}, {new DrawCircleClass({})}));
  // vt.addChild(new Object({}, {new Nsc(.3), new CameraFollow(), new DrawTransform2D(-1, 255, 255, 0, 255)}));
  mainObject->set(vt);

  // vector<ScriptBase *> *scripts = &mainObject->scripts;
  // // scripts->insert(scripts->begin(), new DrawBackgroundClass());
  // scripts->push_back(new DrawBackgroundClass(-1));
  // scripts->push_back(new Nsc());
  // mainObject->scripts.push_back(new DrawBackgroundClass());
}