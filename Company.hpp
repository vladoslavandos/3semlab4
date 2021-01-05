#ifndef COMPANY_HPP
#define COMPANY_HPP

#include "Employee.hpp"
#include "Leader.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Company
{
  std::string label;
  bool subdiv;

public:
  Company(std::string const& label_, bool is_Subdivision = false);
  std::string const& getLabel() const;
};

#endif // COMPANY_HPP
