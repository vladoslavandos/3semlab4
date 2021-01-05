#include "Container.hpp"
#include <algorithm>
// #include "Employee.hpp"

Container::Container(size_t initsize)
    : items{new Employee*[initsize]}, csize{0}, memsize{initsize}
{
}
Container::Container(std::vector<std::pair<int, Employee*>> const& its)
    : items{new Employee*[its.size() + 8]}, csize{0}, memsize{its.size() + 8}
{
  for (auto item : its)
  {
    items[csize]   = item.second;
    codes[csize++] = item.first;
  }

  // std::sort(items, items+csize);
}
Container::~Container()
{
  for (size_t i = 0; i < csize; i++)
    delete items[i];
  delete items;
  delete codes;
}
void Container::release()
{
  for (size_t i = 0; i < csize; i++)
    items[i] = nullptr;
}

size_t Container::size() const { return csize; }

size_t Container::capacity() const { return memsize; }

void Container::push_back(std::pair<int, Employee*> item)
{
  if (memsize == csize)
  {
    auto newsize  = memsize * 2;
    auto tmpitems = new Employee*[newsize];
    auto tmpcodes = new int[newsize];
    std::move(items, items + csize, tmpitems);
    std::move(codes, codes + csize, tmpcodes);
    delete items;
    delete codes;
    items   = tmpitems;
    codes   = tmpcodes;
    memsize = newsize;
  }
  items[csize]   = item.second;
  codes[csize++] = item.first;
}
Employee* Container::remove(int code) { return nullptr; }