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

#include "../buffer/buffer.h"
#include "request/request.h"

namespace network {

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

// Report a failure
void fail(beast::error_code ec, char const *what);

// Echoes back all received WebSocket messages
class Session : public std::enable_shared_from_this<Session> {

public:
  // Take ownership of the socket
  explicit Session(tcp::socket &&socket) : ws_(std::move(socket)) {
    std::cout << "Session Constructor, address " << this << " socket address "
              << &socket << std::endl;
  }

  // Get on the correct executor
  void run();

  // Start the asynchronous operation
  void on_run();

  void on_accept(beast::error_code ec);

  void do_read();

  void on_read(beast::error_code ec, std::size_t bytes_transferred);

  void do_write(const std::string &text);

  void on_write(beast::error_code ec, std::size_t bytes_transferred);

private:
  websocket::stream<beast::tcp_stream> ws_;
  beast::flat_buffer buffer_;

  buffer::Buffer &requestBuffer = buffer::Buffer::getInstance();
};

} // namespace network
