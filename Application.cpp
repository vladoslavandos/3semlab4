#include "Application.hpp"
#include "Company.hpp"
#include "Employee.hpp"
#include "Leader.hpp"

Application::Application() : comp{"My Company"} {};

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
void Application::Fire(int code)
{
  // auto res = comp.find(code);
  // if (res == nullptr)
  //   throw std::runtime_error("Employee with given code was not found.");
  comp.remove(code);
}
void Application::showSubDiv(std::string const& subdivlabel) const
{
  auto res = comp.findBySubDivLabel(subdivlabel);
  if (res == nullptr)
    throw std::runtime_error("Subdivision with given label was not found.");
  res->getSubdiv()->show();
}
void Application::show() const { comp.show(); }

void Application::save(std::ofstream& file) { file << comp.serialize(); }
void Application::open(std::ifstream& file)
{
  if(file.fail())
    throw std::runtime_error("File is corrupted of couldn't be found.");
  comp.clear();
  std::vector<std::pair<int, std::vector<int>>> subdivs;
  std::string label;
  std::getline(file, label, '\n');
  comp.setLabel(label);
  while (!file.eof() && !file.bad())
  {
    int code;
    std::string FIO_;
    int birthdate_;
    std::string post_, education_;
    int salary_, type;
    file >> code;
    file.get();
    std::getline(file, FIO_, ';');
    file >> birthdate_;
    file.get();
    std::getline(file, post_, ';');
    std::getline(file, education_, ';');
    file >> salary_;
    file.get();
    file >> type;
    file.get();
    if (file.eof() || file.bad())
      break;
    if ((EType)type == EType::Usual)
    {
      comp.add(code,
               new Employee{FIO_, birthdate_, post_, education_, salary_});
    }
    else if ((EType)type == EType::Leader)
    {
      std::getline(file, label, ';');
      int count;
      file >> count;
      file.get();
      subdivs.push_back({code, {}});
      for (int i = 0; i < count; i++)
      {
        int subcode;
        file >> subcode;
        file.get();
        subdivs.back().second.push_back(subcode);
      }
      comp.add(code, new Leader{FIO_, birthdate_, post_, education_, salary_,
                                new Company{label, {}, true}});
    }
  }
  for (auto& subdiv : subdivs)
  {
    auto leadersSubdiv = ((Leader*)comp.find(subdiv.first))->getSubdiv();
    for (auto& subcode : subdiv.second)
      leadersSubdiv->add(subcode, comp.find(subcode));
  }
}

Employee* Application::getByCode(int code) const { return comp.find(code); }