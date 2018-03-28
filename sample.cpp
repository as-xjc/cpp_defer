#include <iostream>
#include "defer.h"

class Print {
 public:
  Print(std::string msg) : msg_(msg) {}
  ~Print() {
    std::cout << "message:" << msg_ << std::endl;
  }
  std::string msg_;
};

class test {
 public:
  void Do() {
    int a = 5;
    int b = 6;
    std::cout << "a:" << a << std::endl;
    DEFER(std::cout << "defer b:" << b << std::endl);
    std::cout << "b:" << b << std::endl;
    b = 7;
  }
  void msg(Print* p) {
    delete p;
  }
  void PrintMsg() {
    auto p = new Print("print the msg");
    DEFER_IN_CLASS(msg(p));
  }

};

int main() {

  DEFER(std::cout << "return hello" << std::endl;);
  {
    DEFER(std::cout << "> hello" << std::endl;);
    {
      DEFER(std::cout << ">> hello" << std::endl;
                std::cout << ">> yeah" << std::endl;
                std::cout << ">> hehe" << std::endl;
                std::cout << ">> haah" << std::endl;);
    }
  }
  test t;
  t.Do();
  t.PrintMsg();

  Defer d = Defer([]() {std::cout << "-- im 1" << std::endl; }).
      Then([]() {std::cout << "-- im 2" << std::endl; }).
      Then([]() {std::cout << "-- im 3" << std::endl; }).
      Then([]() {std::cout << "-- im 4" << std::endl; }).
      Then([]() {std::cout << "-- im 5" << std::endl; });
  return 0;
}
