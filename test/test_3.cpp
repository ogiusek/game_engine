#include <iostream>

using namespace std;

class Base
{
public:
  int a = 0;

  void test()
  {
    a += 1;
  }
};

class Derived : public Base
{
public:
  void test()
  {
    Base::test();
    cout << a << endl;
  }
};

int main()
{
  Derived b;
  b.test();
  b.test();
  return 0;
}