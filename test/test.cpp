#include <iostream>
#include <string>

using namespace std;

class A
{
public:
  A(int a) {}
};
class B : public A
{
public:
  B(A a) : A(a) {}
};

int main()
{
  new B(7);
  // jit would be usefull
  // cling::Interpreter interp;
  // std::string task = "std::cout << 7;";
  // interp.declare(task);
  // interp.evaluate();
  return 0;
}