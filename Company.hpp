#ifndef COMPANY_HPP
#define COMPANY_HPP

#include "Container.hpp"
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
          bool is_Subdivision                                 = false);
  std::string const& getLabel() const;
  void setLabel(std::string const&);
  void add(int code, Employee* emp);
  Employee* find(int code) const;
  Leader* findBySubDivLabel(std::string const& label) const;
  Employee*& get(int code);
  void remove(int code);
  void show() const;
  std::string serialize() const;
  void clear();
  ~Company();
};

#endif // COMPANY_HPP
