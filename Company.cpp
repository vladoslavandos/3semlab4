#include "Company.hpp"
#include "Employee.hpp"
#include "Leader.hpp"

Company::Company(std::string const& label_,
                 std::vector<std::pair<int, Employee*>> const& empls,
                 bool is_Subdivision)
    : label{label_}, employees{empls}, subdiv{is_Subdivision} {};

std::string const& Company::getLabel() const { return label; }

Company::~Company()
{
  if (subdiv)
    employees.release();
}

void Company::add(int code, Employee* emp) { employees[code] = emp; }

Employee* Company::find(int code) const
{
  auto tmp = employees.find(code);
  if (tmp != employees.end())
    return tmp->second;
  return nullptr;
}
Employee*& Company::get(int code) { return employees[code]; }
Leader* Company::findBySubDivLabel(std::string const& label) const
{
  for (auto& item : employees)
    if (item.second->getType() == EType::Leader)
    {
      auto leader = ((Leader*)item.second);
      if (leader->getSubdiv()->getLabel() == label)
        return leader;
    }
  return nullptr;
}
void Company::remove(int code) { delete employees.remove(code); }
void Company::show() const
{
  if (subdiv)
  {
    for (auto& item : employees)
      std::cout << item.first << "(" << item.second->getFIO() << ")  ";
  }
  else
    for (auto& item : employees)
    {
      std::cout << item.first << " : ";
      item.second->showInfo();
      std::cout << "\n";
    }
}

std::string Company::serialize() const
{
  std::stringstream ss;
  if (subdiv)
  {
    ss << label << ";" << employees.size() << ";";
    for (auto& item : employees)
      ss << item.first << ";";
  }
  else
  {
    ss << label << "\n";
    for (auto& item : employees)
      ss << item.first << ";" << item.second->serialize() << "\n";
  }
  return ss.str();
}

void Company::setLabel(std::string const& newlabel) { label = newlabel; }

void Company::clear() { employees.clear(); }