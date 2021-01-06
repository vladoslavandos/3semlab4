#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Company.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Application
{
  Company comp;

public:
  Application();
  void Employ(int code, std::string const& FIO_, int birthdate_,
              std::string const& post_, std::string const& education_,
              int salary_);
  void ChangePost(int code, std::string const& newpost_);
  void Employ(int code, std::string const& FIO_, int birthdate_,
              std::string const& post_, std::string const& education_,
              int salary_, Company* subdiv);
  void ChangePost(int code, std::string const& newpost_, Company* subdiv);
  void Fire(int code);
  void showSubDiv(std::string const& subdivlabel) const;
  void show() const;

  void save(std::ofstream& file);
  void open(std::ifstream& file);

  Employee* getByCode(int code) const;
};

#endif // APPLICATION_HPP
