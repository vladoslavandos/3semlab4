#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

class Employee;

class Container
{
private:
  std::pair<int, Employee*>* items;
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

  class iterator : public std::iterator<std::random_access_iterator_tag,
                                        std::pair<int, Employee*>>
  {
  private:
    std::pair<int, Employee*>* item;
    iterator(std::pair<int, Employee*>* aitem);
    friend class Container;

  public:
    iterator(iterator const& other);
    iterator(iterator&& other);
    iterator& operator=(iterator const& other);
    iterator& operator=(iterator&& other);
    iterator& operator++();
    iterator& operator--();
    iterator operator++(int);
    iterator operator--(int);
    std::pair<int, Employee*>& operator*() const;
    std::pair<int, Employee*>* operator->() const;
    iterator operator+(size_t offset) const;
    iterator operator-(size_t offset) const;
    std::ptrdiff_t operator-(iterator const& other) const;
    friend bool operator==(iterator const& lhs, iterator const& rhs);
    friend std::strong_ordering operator<=>(iterator const& lhs,
                                            iterator const& rhs);
  };

  iterator begin();
  iterator end();
  void sort();
};

#endif // CONTAINER_HPP
