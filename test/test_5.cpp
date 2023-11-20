#include <iostream>
#include <unordered_map>

using namespace std;

class XX
{
public:
  string operator()()
  {
    return "cococ";
  }
};

int main()
{
  cout << XX()() << endl;
  return 0;
}