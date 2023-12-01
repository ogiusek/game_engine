#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

// #include <initializer_list>
#include <algorithm>

#include <vector>
// #include <array>

using namespace std;

class Point
{
public:
  float x, y;

  Point(float _x = 0, float _y = 0) : x(_x), y(_y) {}
  Point(int _x, int _y) : x((float)_x), y((float)_y) {}
};

class Poly
{
private:
  float getArea(Point _p1, Point _p2, Point _p3) { return abs(((int)_p1.x * ((int)_p2.y - (int)_p3.y) +
                                                               (int)_p2.x * ((int)_p3.y - (int)_p1.y) +
                                                               (int)_p3.x * ((int)_p1.y - (int)_p2.y)) /
                                                              2.0); }

public:
  Point p[3];
  float getArea() { return getArea(p[0], p[1], p[2]); }
  bool isIn(Point point) { return abs(getArea() - (getArea(p[0], p[1], point) +
                                                   getArea(p[0], point, p[2]) +
                                                   getArea(point, p[1], p[2]))) < 0.00001; }
  Poly rotate(float angle)
  {
    float radians = angle * (M_PI / 180);

    Point midpoint = {(min({p[0].x, p[1].x, p[2].x}) + max({p[0].x, p[1].x, p[2].x})) / 2,
                      (min({p[0].y, p[1].y, p[2].y}) + max({p[0].y, p[1].y, p[2].y})) / 2};
    // Point new_points[3];
    Point new_points[3];
    copy(p, p + 3, new_points);

    for (int i = 0; i < 3; i++)
    {
      // Subtract the midpoint from the vertex
      new_points[i].x -= midpoint.x;
      new_points[i].y -= midpoint.y;

      // Apply the rotation transformation
      float x = new_points[i].x;
      float y = new_points[i].y;
      new_points[i].x = x * cos(radians) - y * sin(radians);
      new_points[i].y = x * sin(radians) + y * cos(radians);

      // Add the midpoint to the new vertex
      new_points[i].x += midpoint.x;
      new_points[i].y += midpoint.y;
    }

    return Poly(new_points[0], new_points[1], new_points[2]); // Return the rotated polygon
  }

  Poly(Point _p1, Point _p2, Point _p3)
  {
    p[0] = _p1;
    p[1] = _p2;
    p[2] = _p3;
  }
};

void drawFilledTriangle(SDL_Renderer *renderer, Poly poly, SDL_Color color = {255, 255, 255})
{

  // if (false) // draw point by point  old method
  // {
  //   // int minX = min({poly.p[0].x, poly.p[1].x, poly.p[2].x}),
  //   //     maxX = max({poly.p[0].x, poly.p[1].x, poly.p[2].x}),
  //   //     minY = min({poly.p[0].y, poly.p[1].y, poly.p[2].y}),
  //   //     maxY = max({poly.p[0].y, poly.p[1].y, poly.p[2].y});
  //   // vector<SDL_Point> points;
  //   // int perf = SDL_GetTicks();
  //   // for (int x = minX; x < maxX; x++)
  //   //   for (int y = minY; y < maxY; y++)
  //   //     if (poly.isIn({(float)x, (float)y}))
  //   //       points.push_back({(int)x, (int)y});
  //   // SDL_RenderDrawPoints(renderer, points.data(), points.size());
  // }

  SDL_Vertex vertexes[] = {{{poly.p[0].x, poly.p[0].y}, color},
                           {{poly.p[1].x, poly.p[1].y}, color},
                           {{poly.p[2].x, poly.p[2].y}, color}};

  SDL_RenderGeometry(renderer, NULL, vertexes, 3, NULL, 0);

  // Poly poly = Poly({{10.0f, 10.0f},
  //                   {10.0f, (float)props.window->height - 10.0f},
  //                   {(float)props.window->width - 10.0f, 10.0f}});
  // drawFilledTriangle(props.window->renderer, poly, {255, 0, 255});
}
