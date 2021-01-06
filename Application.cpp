#include "Application.hpp"
#include "Company.hpp"
#include "Employee.hpp"
#include "Leader.hpp"

void Application::Employ(int code, std::string const& FIO_, int birthdate_,
                         std::string const& post_,
                         std::string const& education_, int salary_)
{
  if (comp.find(code) != nullptr)
    throw std::runtime_error("Employee with same code already exists.");
  comp.add(code, new Employee{FIO_, birthdate_, post_, education_, salary_});
}
void Application::ChangePost(int code, std::string const& newpost_)
{
  auto res = comp.find(code);
  if (res == nullptr)
    throw std::runtime_error("Employee with given code was not found.");
  res->setPost(newpost_);
  if (res->getType() == EType::Leader)
  {
    auto& tmp      = comp.get(code);
    auto newleader = tmp->convertToUsual();
    delete tmp;
    tmp = newleader;
  }
}
void Application::Employ(int code, std::string const& FIO_, int birthdate_,
                         std::string const& post_,
                         std::string const& education_, int salary_,
                         Company* subdiv)
{
  if (comp.find(code) != nullptr)
    throw std::runtime_error("Employee with same code already exists.");
  comp.add(code,
           new Leader{FIO_, birthdate_, post_, education_, salary_, subdiv});
}
void Application::ChangePost(int code, std::string const& newpost_,
                             Company* subdiv)
{
  auto res = comp.find(code);
  if (res == nullptr)
    throw std::runtime_error("Employee with given code was not found.");
  res->setPost(newpost_);
  if (res->getType() == EType::Usual)
  {
    auto& tmp      = comp.get(code);
    auto newleader = tmp->convertToLeader(subdiv);
    delete tmp;
    tmp = newleader;
  }
  else
  {
    ((Leader*)res)->resetSubdiv(subdiv);
  }
}
void Application::Fire(int code) {
  // auto res = comp.find(code);
  // if (res == nullptr)
  //   throw std::runtime_error("Employee with given code was not found.");
  comp.remove(code);
}
void Application::showSubDiv(std::string const& subdivlabel) const {
  auto res = comp.findBySubDivLabel(subdivlabel);
  if(res == nullptr)
    throw std::runtime_error("Subdivision with given label was not found.");
  res->getSubdiv()->show();
}
void Application::show() const {
  comp.show();
}