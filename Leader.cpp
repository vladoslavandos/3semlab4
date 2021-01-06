#include "Leader.hpp"
#include "Company.hpp"

Leader::Leader(std::string const& FIO_, int birthdate_,
               std::string const& post_, std::string const& education_,
               int salary_, Company* subdivision_)
    : Employee{FIO_, birthdate_, post_, education_, salary_},
      subdivision(subdivision_){};

EType Leader::getType() const { return EType::Leader; }

void Leader::showInfo() const
{
  Employee::showInfo();
  std::cout << ", ";
  if (subdivision) {
    std::cout << subdivision->getLabel() << " -> (  ";
    getSubdiv()->show();
    std::cout << ")";
  }
  else
    std::cout << "Empty";
}

Leader::~Leader() { delete subdivision; }

Company* Leader::getSubdiv() const { return subdivision; }

void Leader::resetSubdiv(Company* subdivision_)
{
  delete subdivision;
  subdivision = subdivision_;
}

Employee* Leader::convertToUsual()
{
  delete subdivision;
  return new Employee(*(Employee*)this);
}

Leader* Leader::convertToLeader(Company* subdiv)
{
  throw std::logic_error(
      "Error converting to leader. It is already that type.");
}

std::string Leader::serialize() const
{
  std::stringstream ss;
  ss << Employee::serialize();
  if (!subdivision)
    ss << "0;";
  else
    ss << subdivision->serialize();
  return ss.str();
}