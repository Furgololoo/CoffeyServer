//
// Created by bfurg on 11/10/2023.
//

#include "servermanager.h"
#include "../buffer/buffer.h"

namespace network {

namespace net = boost::asio;      // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

ServerManager::ServerManager(const boost::asio::ip::address &address_,
                             const uint16_t port_,
                             const uint8_t threads_number_)
    : address(address_), port(port_), threads_number(threads_number_) {}

void ServerManager::start() {

  buffer::Buffer::getInstance().setOnDataAvailable(
      std::bind(&ServerManager::startProcessing, this));

  net::io_context ioc{threads_number};

  // Create and launch a listening port
  std::make_shared<Listener>(ioc, tcp::endpoint{address, port})->run();

  std::cout << "Started listening..." << std::endl;
  // Run the I/O service on the requested number of threads
  std::vector<std::thread> v;
  v.reserve(threads_number - 1);
  for (auto i = threads_number - 1; i > 0; --i)
    v.emplace_back([&ioc] { ioc.run(); });
  ioc.run();
}

void ServerManager::startProcessing() {
  request_processing_thread = std::make_unique<std::jthread>(
      &request::RequestProcessing::startWork, &requestProcessing);
  request_processing_thread->detach();
}

} // namespace network