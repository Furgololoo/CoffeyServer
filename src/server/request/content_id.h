//
// Created by furgololoo on 10/14/23.
//

#pragma once
#include <cstdint>

enum class EContentID : uint8_t {
  TICKET = 0x0,
  SPRINT = 0x1,
  USER = 0x2,
  ATTACHMENT = 0x3
};