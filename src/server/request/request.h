//
// Created by furgololoo on 10/14/23.
//

#pragma once

#include "content_id.h"
#include "requestactions.h"

#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <functional>
#include <iostream>

namespace network::request {

namespace json = boost::json;

class Request {
public:
  explicit Request(const json::object &data);

  void setResponse(std::function<void(const std::string &text)> response_);

  void callResponse(const std::string &text) const;

  json::object getContentJson() const;

  ERequestActions getRequestActions() const;
  EContentID getContentID() const;

private:
  ERequestActions action = {};
  EContentID content_id = {};

  json::object content;
  std::string token;
  uint8_t user_id;

  std::function<void(const std::string &text)> response;

  // create request in session
  // pass request to the buffer
  // request process gets request from buffer
  // request process proceed request and sends response to client
};

} // namespace network::request
