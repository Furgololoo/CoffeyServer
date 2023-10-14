//
// Created by bfurg on 11/10/2023.
//

#include "servermanager.h"

namespace network {

namespace net = boost::asio;      // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

ServerManager::ServerManager(const boost::asio::ip::address &address,
                             const unsigned short port, const short threads) {

  // The io_context is required for all I/O
  net::io_context ioc{threads};

  // Create and launch a listening port
  std::make_shared<Listener>(ioc, tcp::endpoint{address, port})->run();

  // Run the I/O service on the requested number of threads
  std::vector<std::thread> v;
  v.reserve(threads - 1);
  for (auto i = threads - 1; i > 0; --i)
    v.emplace_back([&ioc] { ioc.run(); });
  ioc.run();
}
} // namespace network