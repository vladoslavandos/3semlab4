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
  std::cout << ",";
  if (subdivision)
    std::cout << subdivision->getLabel();
  else
    std::cout << "Empty";
}