#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

// #include "Company.hpp"
// #include "Leader.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

enum class EType
{
  Usual,
  Leader
};

class Leader;
class Company;

class Employee
{
private:
  std::string FIO, post, education;
  int birthdate, salary;

public:
  inline Employee(){};
  Employee(std::string const& FIO_, int birthdate_, std::string const& post_,
           std::string const& education_, int salary_);
  virtual void showInfo() const;
  virtual EType getType() const;
  void setPost(std::string const& post_);
  std::string const& getPost() const;
  void setSalary(int salary_);
  int getSalary() const;
  Leader* convertToLeader(Company* subdiv);
  virtual ~Employee() = default;
};

#endif // EMPLOYEE_HPP
