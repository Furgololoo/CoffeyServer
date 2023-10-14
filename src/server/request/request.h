//
// Created by furgololoo on 10/14/23.
//

#pragma once

#include <boost/json.hpp>

namespace network::request {

namespace json = boost::json;

class Request {
public:
  explicit Request(const json &data);
};

} // namespace network::request
