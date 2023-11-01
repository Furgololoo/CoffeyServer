//
// Created by bfurg on 31/10/2023.
//

#pragma once

#include <boost/json/src.hpp>

namespace helper::json {
namespace json = boost::json;
void pretty_print(std::ostream &os, json::value const &jv,
                  std::string *indent = nullptr);
} // namespace helper::json