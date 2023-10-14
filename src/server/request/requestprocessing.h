//
// Created by furgololoo on 10/14/23.
//

#pragma once
#include <boost/json.hpp>

namespace network::request {
namespace json = boost::json;

class RequestManager {
public:
  explicit RequestProcessing(const json::object &data);
};

} // namespace network::request
