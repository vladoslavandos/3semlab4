#include "Company.hpp"

Company::Company(std::string const& label_, bool is_Subdivision)
    : label{label_}, subdiv{is_Subdivision} {};

std::string const& Company::getLabel() const { return label; }