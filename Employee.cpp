#include "Employee.hpp"
#include "Leader.hpp"

Employee::Employee(std::string const& FIO_, int birthdate_,
                   std::string const& post_, std::string const& education_,
                   int salary_)
    : FIO{FIO_}, post{post_}, education{education_}, birthdate{birthdate_},
      salary{salary_}
{
}

std::string const& Employee::getPost() const { return post; }

void Employee::setPost(std::string const& post_) { post = post_; }

int Employee::getSalary() const { return salary; }

void Employee::setSalary(int salary_)
{
  if (salary_ <= 0)
    throw std::logic_error("Salary can't be less or equal to/then zero.");
  salary = salary_;
}

EType Employee::getType() const { return EType::Usual; }

void Employee::showInfo() const
{
  std::cout << FIO << ", " << birthdate << ", " << post << ", " << education
            << ", " << salary;
}

Leader* Employee::convertToLeader(Company* subdiv)
{
  return new Leader(std::move(FIO), birthdate, std::move(post),
                    std::move(education), salary, subdiv);
}

Employee* Employee::convertToUsual() {
  throw std::logic_error("Error converting to usual. It is already that type.");
}