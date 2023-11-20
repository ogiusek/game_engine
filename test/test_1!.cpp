#include <unordered_map>

#include <iostream>
// #include <vector>
// #include <functional>
// #include <thread>
// #include <cmath>
// #include <string>
// #include <map>

using namespace std;

class UniqueTypeStorage
{
private:
  unordered_map<char *, void *> values;

public:
  template <typename T>
  void setValue(T value) { values[(char *)typeid(T).name()] = static_cast<void *>(&value); }

  template <typename T>
  bool exists() { return values.count((char *)typeid(T).name()); }

  template <typename T>
  T getValue() { return *static_cast<T *>(values[(char *)typeid(T).name()]); }
};

int main()
{
  UniqueTypeStorage xxx;
  // xxx.setValue<int>(7);
  if (xxx.exists<string>())
    cout << xxx.getValue<string>() << endl;

  cout << "hello shit\n";

  return 0;
}