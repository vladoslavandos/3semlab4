#include "Container.hpp"
#include "Employee.hpp"
#include "Leader.hpp"
#include <algorithm>

Container::Container(size_t initsize)
    : items{new std::pair<int, Employee*>[initsize]}, csize{0}, memsize{
                                                                    initsize}
{
}
Container::Container(std::vector<std::pair<int, Employee*>> const& its)
    : items{new std::pair<int, Employee*>[its.size() + 8]}, csize{0},
      memsize{its.size() + 8}
{
  for (auto item : its)
    items[csize++] = item;
  sort();
}
Container::~Container()
{
  for (size_t i = 0; i < csize; i++)
    delete items[i].second;
  delete items;
}
void Container::release()
{
  for (size_t i = 0; i < csize; i++)
    items[i].second = nullptr;
}

size_t Container::size() const { return csize; }

size_t Container::capacity() const { return memsize; }

void Container::push_back(std::pair<int, Employee*> item)
{
  if (memsize == csize)
  {
    auto newsize  = memsize * 2;
    auto tmpitems = new std::pair<int, Employee*>[newsize];
    std::move(items, items + csize, tmpitems);
    delete items;
    items   = tmpitems;
    memsize = newsize;
  }
  items[csize++] = item;
  sort();
}
Employee* Container::remove(int code)
{
  Employee* tmp = nullptr;
  for (auto& keyval : *this)
    if (keyval.first == code)
    {
      tmp = keyval.second;
      std::swap(keyval, items[--csize]);
      sort();
      return tmp;
    }
  return tmp;
}

Container::iterator::iterator(std::pair<int, Employee*>* aitem) : item{aitem} {}
Container::iterator::iterator(iterator const& other) : item{other.item} {}
Container::iterator::iterator(iterator&& other) : item{std::move(other.item)} {}
Container::iterator& Container::iterator::operator++()
{
  item++;
  return *this;
}
Container::iterator& Container::iterator::operator--()
{
  item--;
  return *this;
}
Container::iterator Container::iterator::operator++(int)
{
  auto tmp = iterator(*this);
  item++;
  return std::move(tmp);
}
Container::iterator Container::iterator::operator--(int)
{
  auto tmp = iterator(*this);
  item--;
  return std::move(tmp);
}
std::pair<int, Employee*>& Container::iterator::operator*() const
{
  return *item;
}
std::pair<int, Employee*>* Container::iterator::operator->() const
{
  return item;
}
Container::iterator Container::iterator::operator+(size_t offset) const
{
  return iterator{item + offset};
}
Container::iterator Container::iterator::operator-(size_t offset) const
{
  return iterator{item - offset};
}

std::ptrdiff_t Container::iterator::operator-(iterator const& other) const
{
  return item - other.item;
}

Container::iterator& Container::iterator::operator=(iterator const& other)
{
  item = other.item;
  return *this;
}
Container::iterator& Container::iterator::operator=(iterator&& other)
{
  item = other.item;
  return *this;
}

bool operator==(Container::iterator const& lhs, Container::iterator const& rhs)
{
  return lhs.item == rhs.item;
}
std::strong_ordering operator<=>(Container::iterator const& lhs,
                                 Container::iterator const& rhs)
{
  return lhs.item <=> rhs.item;
}
void Container::sort()
{
  std::sort(begin(), end(), [](auto const& lhs, auto const& rhs) {
    return lhs.first < rhs.first;
  });
}
typename Container::iterator Container::begin() { return iterator(items); }
typename Container::iterator Container::end()
{
  return iterator(items + csize);
}