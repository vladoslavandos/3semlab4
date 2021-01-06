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
  Employee*& operator[](int code);
  Employee*& at(int code);
  Employee* at(int code) const;
  void clear();
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

  class const_iterator : public std::iterator<std::random_access_iterator_tag,
                                              std::pair<int, Employee*>>
  {
  private:
    std::pair<int, Employee*> const* item;
    const_iterator(std::pair<int, Employee*> const* aitem);
    friend class Container;

  public:
    const_iterator(const_iterator const& other);
    const_iterator(const_iterator&& other);
    const_iterator& operator=(const_iterator const& other);
    const_iterator& operator=(const_iterator&& other);
    const_iterator& operator++();
    const_iterator& operator--();
    const_iterator operator++(int);
    const_iterator operator--(int);
    std::pair<int, Employee*> const& operator*() const;
    std::pair<int, Employee*> const* operator->() const;
    const_iterator operator+(size_t offset) const;
    const_iterator operator-(size_t offset) const;
    std::ptrdiff_t operator-(const_iterator const& other) const;
    friend bool operator==(const_iterator const& lhs,
                           const_iterator const& rhs);
    friend std::strong_ordering operator<=>(const_iterator const& lhs,
                                            const_iterator const& rhs);
  };

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  iterator find(int code);
  const_iterator find(int code) const;
  void sort();
};

#endif // CONTAINER_HPP
