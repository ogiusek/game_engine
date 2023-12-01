#include <iostream>

#include <unordered_map>
#include <functional>

#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

using namespace std;

class Object;
class ScriptBase
{
public:
  // short int zIndex = 0;
  short int zIndex = 0;
  virtual void Update(Object *object, PerFrameProps *props) {}
  virtual void Draw(Object *object, PerFrameProps *props) {}

  ScriptBase(short int _zIndex = 0) : zIndex(_zIndex) {}
};

class Object : public UniqueTypeStorage
{
private:
  string lastSortedState = "";
  string getScriptsString()
  {
    string result = "";
    for (ScriptBase *script : scripts)
      result += (string)(char *)script + ",";
    return result;
  }

  static bool compareScripts(const ScriptBase *lhs, const ScriptBase *rhs) { return lhs->zIndex < rhs->zIndex; }

  void sortScripts()
  {
    sort(scripts.begin(), scripts.end(), compareScripts);
    lastSortedState = getScriptsString();
  }

public:
  vector<ScriptBase *> scripts;

  void Update(PerFrameProps *props)
  {
    if (lastSortedState != getScriptsString())
      sortScripts();

    for (int i = 0; i < scripts.size(); i++)
      scripts[i]->Update(this, props);
  }

  void Draw(PerFrameProps *props)
  {
    if (lastSortedState != getScriptsString())
      sortScripts();

    for (int i = 0; i < scripts.size(); i++)
      scripts[i]->Draw(this, props);
  }

  Object(UniqueTypeStorage _storage = {}, vector<ScriptBase *> _scripts = {})
      : UniqueTypeStorage(_storage), scripts(_scripts)
  {
    sortScripts();
  }
};