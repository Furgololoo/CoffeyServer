//
// Created by bfurg on 02/11/2023.
//
#pragma once
#include <string>

namespace user {
namespace token {

class Token {

public:
  static std::tuple<std::string> generate();
  static bool check(const std::string &token);
};

} // namespace token
} // namespace user
