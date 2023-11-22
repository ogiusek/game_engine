#include <unordered_map>

using namespace std;

class UniqueTypeStorage
{
private:
  unordered_map<string, void *> values;

public:
  // Basic methods
  template <typename T>
  void unset() { values.erase(typeid(T).name()); }

  template <typename T>
  void set(T value) { values[typeid(T).name()] = new T(value); }

  template <typename T>
  bool exists() { return values.count(typeid(T).name()); }

  template <typename T>
  T get()
  {
    if (!exists<T>())
      throw runtime_error("Requested not existing type from storage");
    return *static_cast<T *>(values[typeid(T).name()]);
  }

  template <typename... T>
  UniqueTypeStorage(T... args) { (set(args), ...); }

  // Additional methods
  template <typename T>
  T get(T defaultVal, bool _set = 0)
  {
    if (!exists<T>())
      if (_set)
        set(defaultVal);
      else
        return defaultVal;

    return *static_cast<T *>(values[typeid(T).name()]);
  }
};