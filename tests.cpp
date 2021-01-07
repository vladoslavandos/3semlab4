#include "Application.hpp"
#include "Employee.hpp"
#include "Leader.hpp"
#include <gtest/gtest.h>

TEST(ApplicationTest, EmploysAndSavesToFile)
{
  Application app;
  app.Employ(12, "name", 2012, "manager", "higher", 10000);
  app.Employ(5, "surname", 2010, "callcenter", "school", 8000);
  std::stringstream ss;
  app.save((std::ofstream&)ss);
  ASSERT_EQ(ss.str(), R"(My Company
5;surname;2010;callcenter;school;8000;1;
12;name;2012;manager;higher;10000;1;
)");
}

TEST(ApplicationTest, ChangesPost) {
  Application app;
  app.Employ(12, "name", 2012, "manager", "higher", 10000);
  app.Employ(5, "surname", 2010, "callcenter", "school", 8000);
  app.ChangePost(12, "post");
  ASSERT_EQ(app.getByCode(12)->getPost(), "post");
}

TEST(ApplicationTest, CanFire) {
  Application app;
  app.Employ(12, "name", 2012, "manager", "higher", 10000);
  app.Employ(5, "surname", 2010, "callcenter", "school", 8000);
  app.Employ(13, "someone", 13, "somepost", "education1", 100000);
  app.Fire(13);
  ASSERT_EQ(app.getByCode(13), nullptr);
  std::stringstream ss;
  app.save((std::ofstream&)ss);
  ASSERT_EQ(ss.str(), R"(My Company
5;surname;2010;callcenter;school;8000;1;
12;name;2012;manager;higher;10000;1;
)");
}

TEST(ApplicationTest, CanLoadFromFile) {
  Application app;
  app.Employ(12, "name", 2012, "manager", "higher", 10000);
  app.Employ(5, "surname", 2010, "callcenter", "school", 8000);
  app.Employ(13, "someone", 13, "somepost", "education1", 100000);
  std::stringstream ss;
  app.save((std::ofstream&)ss);
  app.open((std::ifstream&)ss);
  ss.str();
  app.save((std::ofstream&)ss);
  ASSERT_EQ(ss.str(), R"(My Company
5;surname;2010;callcenter;school;8000;1;
12;name;2012;manager;higher;10000;1;
13;someone;13;somepost;education1;100000;1;
)");
}