#ifndef COMPANY_HPP
#define COMPANY_HPP

#include "Container.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief can be forward declared here bc Company class only uses pointer to
 * them
 *
 */
class Employee;
/**
 * @brief can be forward declared here bc Company class only uses pointer to
 * them
 *
 */
class Leader;
/**
 * @brief Company describer class
 *
 */
class Company
{
  /**
   * @brief The label of company
   *
   */
  std::string label;
  /**
   * @brief Container class containing Employee pointers
   *
   */
  Container<Employee> employees;
  /**
   * @brief is company actually describing a subdivision
   *
   */
  bool subdiv;

public:
  /**
   * @brief Construct a new Company object
   *
   * @param label_
   * @param empls
   * @param is_Subdivision
   */
  Company(std::string const& label_,
          std::vector<std::pair<int, Employee*>> const& empls = {},
          bool is_Subdivision                                 = false);
  /**
   * @brief Get the Label of company
   *
   * @return std::string const&
   */
  std::string const& getLabel() const;
  /**
   * @brief Set the Label of company
   * 
   */
  void setLabel(std::string const&);
  /**
   * @brief Add new employee to company
   * 
   * @param code unique indentifier of employee
   * @param emp a pointer to employee's object
   */
  void add(int code, Employee* emp);
  /**
   * @brief Find an employee by his id
   * 
   * @param code unique indentifier of employee
   * @return Employee* 
   */
  Employee* find(int code) const;
  /**
   * @brief Find subdivision by its label
   * 
   * @param label 
   * @return Leader* 
   */
  Leader* findBySubDivLabel(std::string const& label) const;
  /**
   * @brief Get an emloyee pointer reference
   * differs from find<br>
   * throws an exception if employee with such a code was not found in table
   * 
   * @param code 
   * @return Employee*& 
   */
  Employee*& get(int code);
  /**
   * @brief Remove employee from table by his id
   * 
   * @param code 
   */
  void remove(int code);
  /**
   * @brief Prints the entire table to std::cout
   * 
   */
  void show() const;
  /**
   * @brief serializes company to make it writable to file for example
   * 
   * @return std::string 
   */
  std::string serialize() const;
  /**
   * @brief Removes all employees from table
   * 
   */
  void clear();
  /**
   * @brief Destroy the Company object
   * 
   */
  ~Company();
};

#endif // COMPANY_HPP
