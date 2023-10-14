//
// Created by bfurg on 11/10/2023.
//

#pragma once

#include "listener.h"
#include <boost/asio/strand.hpp>

namespace network {

class ServerManager {

public:
  explicit ServerManager(const boost::asio::ip::address &address,
                         const unsigned short port, const short threads);
};

} // namespace network
