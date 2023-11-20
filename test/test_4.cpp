#include <iostream>
#include <vector>

using namespace std;

class XXX;

class Base
{
public:
  virtual void test(XXX *x) { cout << "not overrided\n"; }
};

class XXX
{
};
class Derived : public Base
{
public:
  void test(XXX *x) override { cout << "overrided\n"; }
};

int main()
{
  vector<Base *> vec; // to override need to use ptr's
  vec.push_back(new Derived());
  vec[0]->test(new XXX());
  // vec[0]->test();
  return 0;
}