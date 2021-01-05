#include "Company.hpp"

Company::Company(std::string const& label_,
                 std::vector<std::pair<int, Employee*>> const& empls = {},
                 bool is_Subdivision = false)
    : label{label_}, employees{empls}, subdiv{is_Subdivision} {};

std::string const& Company::getLabel() const { return label; }
