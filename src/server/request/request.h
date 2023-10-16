//
// Created by furgololoo on 10/14/23.
//

#pragma once

#include "requestactions.h"
#include <boost/json.hpp>

namespace network::request {

namespace json = boost::json;

class Request {
public:
  Request() = default;

  void processRequest(const json::object &data);

private:
  bool validateRequest(const json::object &data);

  // database pointer
};

} // namespace network::request
