#include <SDL2/SDL.h>
#include <vector>

#include <iostream>
using namespace std;

class Inputs
{
private:
  vector<uint> held_keys = {},
               pressed_keys = {};

public:
  Mouse mouse;

  bool isHeld(uint key)
  {
    for (uint held_key : held_keys)
      if (held_key == key)
        return 1;
    return 0;
  }

  bool isPressed(uint key)
  {
    for (uint pressed_key : pressed_keys)
      if (pressed_key == key)
        return 1;
    return 0;
  }

  void addPressed(uint key)
  {
    pressed_keys.push_back(key);
  }

  void clearPressed()
  {
    pressed_keys.clear();
    mouse.clearPressed();
  }

  void addHeld(uint key)
  {
    for (int i = 0; i < held_keys.size(); i++)
      if (held_keys.at(i) == key)
        return;

    held_keys.push_back(key);
  }

  void removeHeld(uint key)
  {
    auto it = held_keys.begin();
    while (it != held_keys.end())
      if (*it == key)
        it = held_keys.erase(it);
      else
        ++it;
  }

  void coutAll()
  {
    // if (held_keys.size())
    // {
    //   cout << "held keys are: ";

    //   for (uint held : held_keys)
    //     cout << held << ", ";
    //   cout << "\n";
    // }
    if (pressed_keys.size())
    {
      cout << "pressed keys are: ";

      for (uint pressed : pressed_keys)
        cout << pressed << ", ";
      cout << "\n";
    }
    mouse.coutAll();
  }
};