#include "Company.hpp"
#include "Employee.hpp"
#include "Leader.hpp"
#include <iostream>

int main(int argc, char const* argv[])
{
  Container a{{{12, new Employee{"12", 12, "post", "edu", 12000}},
               {1, new Employee{"1", 1, "post1", "educ", 35000}},
               {13, new Leader{"leader", 13, "ExecDirector", "edu", 1000000,
                               nullptr}}}};
  a.push_back({2, new Leader{"le2", 2, "Leader2", "educat", 150000, nullptr}});
  a.remove(12);
  for (auto& item : a)
  {
    item.second->showInfo();
    std::cout << "\n";
  }
  return 0;
}
