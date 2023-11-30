//
// Created by furgololoo on 10/14/23.
//

#pragma once
#include <cstdint>

namespace network::request {
enum class ERequestActions : uint8_t {
  GET = 1,
  CREATE = 2,
  UPDATE = 3,
  REMOVE = 4,
  CLOSE_SESSION = 5,
  LOGIN = 6,
  TEST = 7
};
}
