//
// Created by bfurg on 31/10/2023.
//

#pragma once

#include <iostream>
#include <boost/json.hpp>

namespace helper::json {
namespace json = boost::json;

void pretty_print(std::ostream &, json::value const &jv,
                  std::string *indent = nullptr);

} // namespace helper::json


