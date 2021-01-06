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
  if (subdivision)
    std::cout << subdivision->getLabel();
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

Employee* Leaeder::convertToUsual()
{
  delete subdivision;
  return new Employee(std::move(FIO), birthdate, std::move(post),
                      std::move(education), salary);
}


Leader* Leader::convertToLeader(Company* subdiv) {
  throw std::logic_error("Error converting to leader. It is already that type.");
}