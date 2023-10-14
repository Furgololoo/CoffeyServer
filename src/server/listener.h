//
// Created by furgololoo on 10/14/23.
//

#pragma once

#include <algorithm>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "session.h"

namespace network {

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

// Accepts incoming connections and launches the sessions
class Listener : public std::enable_shared_from_this<Listener> {

public:
  Listener(net::io_context &ioc, tcp::endpoint endpoint);
  // Start accepting incoming connections
  void run() { do_accept(); }

private:
  void do_accept();

  void on_accept(beast::error_code ec, tcp::socket socket);

  net::io_context &ioc_;
  tcp::acceptor acceptor_;
};

} // namespace network
