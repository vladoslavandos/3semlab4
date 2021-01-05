#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Employee;

class Container
{
private:
  Employee** items;
  int* codes;
  size_t memsize;
  size_t csize;
public:
  Container(size_t initsize = 8);
  Container(std::vector<std::pair<int, Employee*>> const& its);
  ~Container();
  void release();
  size_t size() const;
  size_t capacity() const;
  void push_back(std::pair<int, Employee*> item);
  Employee* remove(int code);
};

#endif // CONTAINER_HPP
