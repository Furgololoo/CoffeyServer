//
// Created by bfurg on 02/11/2023.
//

#include "token.h"

namespace user {
namespace token {
std::string Token::generate() {
  std::string str("Asddasdasads");
  return str;
}
bool Token::check(const std::string &token) { return !token.empty(); }
} // namespace token
} // namespace user