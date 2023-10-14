#include <boost/version.hpp>
#include <iostream>

#include "server/request/request.h"
#include "server/servermanager.h"

int main() {
  if constexpr (BOOST_VERSION < 108200) {
    std::cerr << "Bad Boost Version: " << BOOST_VERSION
              << ", should be 108300 or higher " << std::endl;
    return 1;
  }

  //  namespace net = boost::asio;
  //  network::ServerManager server_manager(net::ip::make_address("127.0.0.1"),
  //                                        9999, 1);

  namespace json = boost::json;

  json::object obj;
  obj["type"] = 0;
  obj["action"] = 0;
  obj["content_id"] = 35;
  return 0;
}