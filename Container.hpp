#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "Employee.hpp"
#include "Leader.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

class Employee;

template <typename Base>
class Container
{
public:
  using pointer_type = Base*;
  using pair_type    = std::pair<int, pointer_type>;

private:
  pair_type* items;
  size_t memsize;
  size_t csize;

public:
  Container(size_t initsize)
      : items{new pair_type[initsize]}, csize{0}, memsize{initsize}
  {
  }
  Container(std::vector<pair_type> const& its)
      : items{new pair_type[its.size() + 8]}, csize{0}, memsize{its.size() + 8}
  {
    for (auto item : its)
      items[csize++] = item;
    sort();
  }
  ~Container()
  {
    for (size_t i = 0; i < csize; i++)
      delete items[i].second;
    delete[] items;
  }
  void release()
  {
    for (size_t i = 0; i < csize; i++)
      items[i].second = nullptr;
  }

  size_t size() const { return csize; }

  size_t capacity() const { return memsize; }

  void push_back(pair_type item)
  {
    if (memsize == csize)
    {
      auto newsize  = memsize * 2;
      auto tmpitems = new pair_type[newsize];
      std::move(items, items + csize, tmpitems);
      delete[] items;
      items   = tmpitems;
      memsize = newsize;
    }
    items[csize++] = item;
    sort();
  }
  pointer_type remove(int code)
  {
    pointer_type tmp = nullptr;
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
  class iterator
      : public std::iterator<std::random_access_iterator_tag, pair_type>
  {
  private:
    pair_type* item;
    iterator(pair_type* aitem) : item{aitem} {}
    friend class Container;

  public:
    iterator(iterator const& other) : item{other.item} {}
    iterator(iterator&& other) : item{std::move(other.item)} {}
    Container::iterator& operator++()
    {
      item++;
      return *this;
    }
    Container::iterator& operator--()
    {
      item--;
      return *this;
    }
    Container::iterator operator++(int)
    {
      auto tmp = iterator(*this);
      item++;
      return std::move(tmp);
    }
    Container::iterator operator--(int)
    {
      auto tmp = iterator(*this);
      item--;
      return std::move(tmp);
    }
    pair_type& operator*() const { return *item; }
    pair_type* operator->() const { return item; }
    Container::iterator operator+(size_t offset) const
    {
      return iterator{item + offset};
    }
    Container::iterator operator-(size_t offset) const
    {
      return iterator{item - offset};
    }

    std::ptrdiff_t operator-(iterator const& other) const
    {
      return item - other.item;
    }

    Container::iterator& operator=(iterator const& other)
    {
      item = other.item;
      return *this;
    }
    Container::iterator& operator=(iterator&& other)
    {
      item = other.item;
      return *this;
    }
    friend bool operator==(Container::iterator const& lhs,
                           Container::iterator const& rhs)
    {
      return lhs.item == rhs.item;
    }
    friend std::strong_ordering operator<=>(Container::iterator const& lhs,
                                            Container::iterator const& rhs)
    {
      return lhs.item <=> rhs.item;
    }
  };

  class const_iterator
      : public std::iterator<std::random_access_iterator_tag, pair_type>
  {
  private:
    pair_type const* item;
    const_iterator(pair_type const* aitem) : item{aitem} {}
    friend class Container;

  public:
    const_iterator(const_iterator const& other) : item{other.item} {}
    const_iterator(const_iterator&& other) : item{std::move(other.item)} {}
    Container::const_iterator& operator++()
    {
      item++;
      return *this;
    }
    Container::const_iterator& operator--()
    {
      item--;
      return *this;
    }
    Container::const_iterator operator++(int)
    {
      auto tmp = const_iterator(*this);
      item++;
      return std::move(tmp);
    }
    Container::const_iterator operator--(int)
    {
      auto tmp = const_iterator(*this);
      item--;
      return std::move(tmp);
    }
    pair_type const& operator*() const { return *item; }
    pair_type const* operator->() const { return item; }
    Container::const_iterator operator+(size_t offset) const
    {
      return const_iterator{item + offset};
    }
    Container::const_iterator operator-(size_t offset) const
    {
      return const_iterator{item - offset};
    }

    std::ptrdiff_t operator-(const_iterator const& other) const
    {
      return item - other.item;
    }

    Container::const_iterator& operator=(const_iterator const& other)
    {
      item = other.item;
      return *this;
    }
    Container::const_iterator& operator=(const_iterator&& other)
    {
      item = other.item;
      return *this;
    }
    friend bool operator==(Container::const_iterator const& lhs,
                           Container::const_iterator const& rhs)
    {
      return lhs.item == rhs.item;
    }
    friend std::strong_ordering
    operator<=>(Container::const_iterator const& lhs,
                Container::const_iterator const& rhs)
    {
      return lhs.item <=> rhs.item;
    }
  };
  void sort()
  {
    std::sort(begin(), end(), [](auto const& lhs, auto const& rhs) {
      return lhs.first < rhs.first;
    });
  }
  iterator begin() { return iterator(items); }
  iterator end() { return iterator(items + csize); }
  const_iterator begin() const { return const_iterator(items); }
  const_iterator end() const { return const_iterator(items + csize); }

  pointer_type& operator[](int code)
  {
    for (auto& keyval : *this)
      if (keyval.first == code)
        return keyval.second;
    push_back({code, nullptr});
    // items[csize++] = pair_type{code, nullptr};
    // sort();
    return at(code);
  }
  pointer_type& at(int code)
  {
    for (auto& keyval : *this)
      if (keyval.first == code)
        return keyval.second;
    throw std::runtime_error("Code was not found!");
  }
  pointer_type at(int code) const
  {
    for (auto& keyval : *this)
      if (keyval.first == code)
        return keyval.second;
    throw std::runtime_error("Code was not found!");
  }

  iterator find(int code)
  {
    auto it = begin();
    for (; it != end(); ++it)
      if (it->first == code)
        break;
    return it;
  }
  const_iterator find(int code) const
  {
    auto it = begin();
    for (; it != end(); ++it)
      if (it->first == code)
        break;
    return it;
  }

  void clear()
  {
    for (size_t i = 0; i < csize; i++)
      delete items[i].second;
    csize = 0;
  }
};

#endif // CONTAINER_HPP
