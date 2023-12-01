#include <iostream>

#include <unordered_map>
#include <functional>
#include <algorithm>

#include <SDL2/SDL.h>
#include <vector>
#include <cmath>

using namespace std;

class VectorTree
{
private:
  Object *thisObject;
  vector<Object *> children;
  vector<Object *> grandChildren;

protected:
  Object *parent = nullptr;
  void refreshGrandChildren()
  {
    grandChildren = {};
    if (parent != nullptr && parent->exists<VectorTree>())
      parent->get<VectorTree>().refreshGrandChildren();
  }

public:
  void assignParrent(Object *ptr) { parent = ptr; }
  Object *getParent(bool withNested = 0)
  {
    if (!withNested)
      return parent;
    if (parent == nullptr)
      return thisObject;
    return parent->get<VectorTree>().getParent(withNested);
  }

  void removeChild(Object *ptr)
  {
    children.erase(remove_if(children.begin(), children.end(),
                             [ptr](Object *pt)
                             { return ptr != pt; }),
                   children.end());
    refreshGrandChildren();
  }

  void addChild(Object *child)
  {
    VectorTree childVectorTree = child->get<VectorTree>(VectorTree(child));
    childVectorTree.assignParrent(thisObject);
    child->set(childVectorTree);

    children.push_back(child);
    refreshGrandChildren();
  }

  vector<Object *> getChildren(bool withNested = 0)
  {
    if (!withNested)
      return children;

    if (grandChildren.size() != 0 ||
        children.size() == 0)
      return grandChildren;

    for (Object *child : children)
      grandChildren.push_back(child);

    for (Object *child : children)
      if (child->exists<VectorTree>())
        for (Object *grandChild : child->get<VectorTree>().getChildren(1))
          grandChildren.push_back(grandChild);

    thisObject->set<VectorTree>(*this);
    return grandChildren;
  }

  VectorTree(Object *_thisObject) : thisObject(_thisObject) {}
};

class VectorScript : public ScriptBase
{
public:
  void Update(Object *object, PerFrameProps *props) override
  {
    vector<Object *> children = object->get<VectorTree>(VectorTree(object), 1).getChildren(1);
    for (Object *child : children)
      child->Update(props);
  }

  void Draw(Object *object, PerFrameProps *props) override
  {
    vector<Object *> children = object->get<VectorTree>(VectorTree(object), 1).getChildren(1);
    for (Object *child : children)
      child->Draw(props);
  }
};