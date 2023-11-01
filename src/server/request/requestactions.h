//
// Created by furgololoo on 10/14/23.
//

#pragma once
#include <cstdint>

namespace network::request {
enum class ERequestActions : uint8_t {
  GET = 0x0,
  CREATE = 0x1,
  UPDATE = 0x2,
  REMOVE = 0x4,
  CLOSE_SESSION = 0x8
};
}