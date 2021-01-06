#ifndef COMPANY_HPP
#define COMPANY_HPP

// #include "Employee.hpp"
// #include "Leader.hpp"
#include "Container.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Employee;
class Leader;

class Company
{
  std::string label;
  Container employees;
  bool subdiv;

public:
  Company(std::string const& label_,
          std::vector<std::pair<int, Employee*>> const& empls = {},
          bool is_Subdivision = false);
  std::string const& getLabel() const;
  void add(int code, Employee* emp);
  Employee* find(int code) const;
  Leader* findBySubDivLabel(std::string const& label) const;
  void remove(int code);
  void show() const;
  ~Company();
};

#endif // COMPANY_HPP
