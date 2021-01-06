#ifndef LEADER_HPP
#define LEADER_HPP

#include "Employee.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Company;

class Leader : public Employee
{
private:
  Company* subdivision;

public:
  inline Leader() : subdivision{nullptr} {};
  Leader(std::string const& FIO_, int birthdate_, std::string const& post_,
         std::string const& education_, int salary_, Company* subdivision_);
  ~Leader();

  void showInfo() const override;
  std::string serialize() const override;
  EType getType() const override;
  Company* getSubdiv() const;
  void resetSubdiv(Company* subdivision_);
  Leader* convertToLeader(Company* subdiv) override;
  Employee* convertToUsual() override;
};

// Leader a{"FIO", 1, "asd", "3", 2, nullptr};
// Employee b{"FIO", 1, "asd", "3", 2};

#endif // LEADER_HPP
