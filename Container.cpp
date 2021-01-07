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
  delete[] items;
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
typename Container::const_iterator Container::begin() const
{
  return const_iterator(items);
}
typename Container::const_iterator Container::end() const
{
  return const_iterator(items + csize);
}

Employee*& Container::operator[](int code)
{
  for (auto& keyval : *this)
    if (keyval.first == code)
      return keyval.second;
  items[csize++] = std::pair<int, Employee*>{code, nullptr};
  sort();
  return at(code);
}
Employee*& Container::at(int code)
{
  for (auto& keyval : *this)
    if (keyval.first == code)
      return keyval.second;
  throw std::runtime_error("Code was not found!");
}
Employee* Container::at(int code) const
{
  for (auto& keyval : *this)
    if (keyval.first == code)
      return keyval.second;
  throw std::runtime_error("Code was not found!");
}

Container::const_iterator::const_iterator(
    std::pair<int, Employee*> const* aitem)
    : item{aitem}
{
}
Container::const_iterator::const_iterator(const_iterator const& other)
    : item{other.item}
{
}
Container::const_iterator::const_iterator(const_iterator&& other)
    : item{std::move(other.item)}
{
}
Container::const_iterator& Container::const_iterator::operator++()
{
  item++;
  return *this;
}
Container::const_iterator& Container::const_iterator::operator--()
{
  item--;
  return *this;
}
Container::const_iterator Container::const_iterator::operator++(int)
{
  auto tmp = const_iterator(*this);
  item++;
  return std::move(tmp);
}
Container::const_iterator Container::const_iterator::operator--(int)
{
  auto tmp = const_iterator(*this);
  item--;
  return std::move(tmp);
}
std::pair<int, Employee*> const& Container::const_iterator::operator*() const
{
  return *item;
}
std::pair<int, Employee*> const* Container::const_iterator::operator->() const
{
  return item;
}
Container::const_iterator
Container::const_iterator::operator+(size_t offset) const
{
  return const_iterator{item + offset};
}
Container::const_iterator
Container::const_iterator::operator-(size_t offset) const
{
  return const_iterator{item - offset};
}

std::ptrdiff_t
Container::const_iterator::operator-(const_iterator const& other) const
{
  return item - other.item;
}

Container::const_iterator&
Container::const_iterator::operator=(const_iterator const& other)
{
  item = other.item;
  return *this;
}
Container::const_iterator&
Container::const_iterator::operator=(const_iterator&& other)
{
  item = other.item;
  return *this;
}

bool operator==(Container::const_iterator const& lhs,
                Container::const_iterator const& rhs)
{
  return lhs.item == rhs.item;
}
std::strong_ordering operator<=>(Container::const_iterator const& lhs,
                                 Container::const_iterator const& rhs)
{
  return lhs.item <=> rhs.item;
}

Container::iterator Container::find(int code)
{
  auto it = begin();
  for (; it != end(); ++it)
    if (it->first == code)
      break;
  return it;
}
Container::const_iterator Container::find(int code) const
{
  auto it = begin();
  for (; it != end(); ++it)
    if (it->first == code)
      break;
  return it;
}

void Container::clear()
{
  for (size_t i = 0; i < csize; i++)
    delete items[i].second;
  csize = 0;
}