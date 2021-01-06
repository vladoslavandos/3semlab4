#include "Application.hpp"
#include "Company.hpp"
#include "Employee.hpp"
#include "Leader.hpp"
#include <iostream>

int main(int argc, char const* argv[])
{
  Application app;
  app.Employ(12, "12", 12, "post", "edu", 12000);
  app.Employ(1, "1", 1, "post1", "educ", 35000);
  app.Employ(13, "leader", 13, "ExecDirector", "edu", 1000000,
             new Company{"leader 13's subdiv", {{1, app.getByCode(1)}}, true});
  app.Employ(2, "le2", 2, "Leader2", "educat", 150000,
             new Company{"le2's subdiv",
                         {{12, app.getByCode(12)}, {1, app.getByCode(1)}},
                         true});
  app.show();
  std::ofstream file{"tab.csv"};
  app.save(file);
  file.close();
  std::ifstream ifile{"tab.csv"};
  app.open(ifile);
  ifile.close();
  app.show();
  // Container a{{{12, new Employee{"12", 12, "post", "edu", 12000}},
  //              {1, new Employee{"1", 1, "post1", "educ", 35000}},
  //              {13, new Leader{"leader", 13, "ExecDirector", "edu",
  //              1000000,
  //                              nullptr}}}};
  // a.push_back({2, new Leader{"le2", 2, "Leader2", "educat", 150000,
  // nullptr}}); a.remove(12); for (auto& item : a)
  // {
  //   item.second->showInfo();
  //   std::cout << "\n";
  // }
  return 0;
}
