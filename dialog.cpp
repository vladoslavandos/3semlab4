#include "Application.hpp"
#include "Employee.hpp"
#include "Leader.hpp"

void employ(Application& app)
{
  int code;
  std::string name;
  int birthday;
  std::string post, educ;
  int salary;
  std::cout << "Input unique code for employee: ";
  std::cin >> code;
  std::cout << "Input name of employee: ";
  std::cin >> name;
  std::cout << "Input date of birth of employee: ";
  std::cin >> birthday;
  std::cout << "Input post of employee: ";
  std::cin >> post;
  std::cout << "Input education of employee: ";
  std::cin >> educ;
  std::cout << "Input salary of employee: ";
  std::cin >> salary;
  try
  {
    app.Employ(code, name, birthday, post, educ, salary);
  }
  catch (std::runtime_error& e)
  {
    std::cerr << e.what() << std::endl;
  }
}
void exit(Application& app) { exit(0); }
void change_post(Application& app)
{
  int code;
  std::string newpost;
  std::cout << "Input unique code of employee: ";
  std::cin >> code;
  std::cout << "Input the new post for employee: ";
  std::cin >> newpost;
  try
  {
    app.ChangePost(code, newpost);
  }
  catch (std::runtime_error& e)
  {
    std::cerr << e.what() << std::endl;
  }
}
void fire(Application& app)
{
  int code;
  std::cout << "Input unique code of employee to be fired: ";
  std::cin >> code;
  try
  {
    app.Fire(code);
  }
  catch (std::runtime_error& e)
  {
    std::cerr << e.what() << std::endl;
  }
}
void show_subdivision(Application& app) {
  std::string label;
  std::cout << "Input label of subdivision: ";
  std::cin >> label;
  try
  {
    app.showSubDiv(label);
  }
  catch (std::runtime_error& e)
  {
    std::cerr << e.what() << std::endl;
  }
}
void show_table(Application& app) {
  app.show();
}
void save_table(Application& app) {
  std::string filename;
  std::cout << "Input file path to write to: ";
  std::cin >> filename;
  try
  {
    std::ofstream file{filename};
    app.save(file);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}
void open_table(Application& app) {
  std::string filename;
  std::cout << "Input file path to read from: ";
  std::cin >> filename;
  try
  {
    std::ifstream file{filename};
    app.open(file);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

// static means it's invisible for another translation units
static void (*opts[])(Application&) = {
    exit,       employ,     change_post, fire, show_subdivision,
    show_table, save_table, open_table};

int main(int argc, char const* argv[])
{
  Application app;
  char ch = '0';
  while (ch != '1')
  {
    std::cout << R"(
Choose an option:
[1] Exit
[2] Employ
[3] Change post
[4] Fire
[5] Show subdivision by label
[6] Show the entire table
[7] Save table to file
[8] Load table from file
>>  )";
    std::cin >> ch;
    if (ch-'0' <= 0 || ch-'0' > sizeof(opts) / sizeof(void*))
    {
      std::cout << "Invalid option! Try again.\n";
      continue;
    }
    opts[ch - '1'](app);
    std::cout << std::endl;
  }
  return 0;
}
