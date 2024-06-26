//
// Created by bfurg on 18/10/2023.
//

#pragma once

#include <cstdint>
#include <string_view>

namespace database {
const std::string_view kDBOptions = "dbname=coffeydb user=postgres password="
    "2Zkut1B0$$ hostaddr=127.0.0.1 port=5432";
} // namespace database

namespace Login {
constexpr int kTokenValidityDays = 5;
}

namespace buffer {
constexpr const uint16_t kBufferSize = 4;
} // namespace buffer
