#include <SDL2/SDL.h>
#include <vector>

#include <iostream>
using namespace std;

class Mouse
{
private:
  vector<int> held = {},
              pressed = {};

public:
  int x = 0, y = 0,
      lastX = 0, lastY = 0,
      scroll = 0;

  bool isHeld(int btn)
  {
    for (int held_btn : held)
      if (held_btn == btn)
        return 1;
    return 0;
  }

  bool isPressed(int btn)
  {
    for (char pressed_btn : pressed)
      if (pressed_btn == btn)
        return 1;
    return 0;
  }

  void addPressed(int btn)
  {
    pressed.push_back(btn);
  }

  void clearPressed()
  {
    scroll = 0;
    pressed.clear();
  }

  void setX(int _x)
  {
    lastX = x;
    x = _x;
  }

  void setY(int _y)
  {
    lastX = y;
    y = _y;
  }

  void setXY(int _x, int _y)
  {
    setX(_x);
    setY(_y);
  }

  void addHeld(int btn)
  {
    for (int i = 0; i < held.size(); i++)
      if (held.at(i) == btn)
        return;

    held.push_back(btn);
  }

  void removeHeld(int btn)
  {
    auto it = held.begin();
    while (it != held.end())
      if (*it == btn)
        it = held.erase(it);
      else
        ++it;
  }

  void coutAll()
  {
    if (scroll)
      cout << "Scroll is " << scroll << endl;

    // if (held.size())
    // {
    //   cout << "held buttons are: ";

    //   for (int held : held)
    //     cout << held << ", ";
    //   cout << "\n";
    // }
    if (pressed.size())
    {
      cout << "pressed buttons are: ";

      for (int pressed : pressed)
        cout << pressed << ", ";
      cout << "\n";
    }
  }
};
