#include <type_traits>
#include <iostream>
#include <vector>
#include <functional>
#include <thread>
#include <cmath>
#include <string>

using namespace std;

class A
{
public:
  char *dist;

  // template <typename T>
  // A(T publicValue)
  // {
  //   if (is_pointer<T>::publicValue)
  //     dist = reinterpret_cast<char *>(&publicValue);
  //   else
  //     dist = reinterpret_cast<char *>(publicValue);
  // }

  template <typename T>
  T get(string wanted)
  {
    if (wanted == "a")
      return 1;
    else if (wanted == "b")
      return 2.0;
  }

  void operator>(char *dd)
  {
    cout << *dd << endl;
  }

  // template <typename T>
  // T GetPublic()
  // {
  //   T *response = reinterpret_cast<T *>(dist);
  //   return *response;
  // }
};

template <typename T>
void test(T value)
{
  // A test = A(value);
  A test = A();

  // test > (char *)"way";
  cout << test.get<string>("a") << endl;
  cout << test.get<int>("b") << endl;
  // cout << test.get("c") << endl;

  // T res = test.GetPublic<T>();
  // cout << res << endl;
}

int main()
{

  float x = 9.11;
  // test<float *>((float *)&x);
  test<float>((float)x);
  // vector<A> ais;
  // ais.push_back(A(7));
  // ais[0].func();

  // ais[0].nVal;

  cout << "hello shit\n";

  return 0;
}