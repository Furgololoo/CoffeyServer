//
// Created by bfurg on 11/10/2023.
//

#pragma once

#include "listener.h"
#include "request/requestprocessing.h"
#include <boost/asio/strand.hpp>
#include <memory>
#include <thread>

namespace network {

class ServerManager {

public:
  explicit ServerManager(const boost::asio::ip::address &address,
                         const uint16_t port, const uint8_t threads);

  void start();

  void startProcessing();

private:
  std::unique_ptr<std::jthread> request_processing_thread;
  request::RequestProcessing requestProcessing;

  boost::asio::ip::address address;
  uint16_t port;
  uint8_t threads_number;
};

} // namespace network
