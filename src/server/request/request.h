//
// Created by furgololoo on 10/14/23.
//

#pragma once

#include "content_id.h"
#include "requestactions.h"

#include <boost/json.hpp>
#include <iostream>

namespace network::request {

namespace json = boost::json;

class Request {
public:
  //  explicit Request(const json::object &data);
  Request(int id_) : id(id_) { /*std::cout << "constructing request\n";*/
  }

  ~Request() { /*std::cout << "deleting request\n";*/
  }
  int id;

private:
  //  ERequestActions actions = {};
  //  EContentID content_id = {};

  // create request in session
  // pass request to the buffer
  // request process gets request from buffer
  // request process proceed request and sends response to client
};

} // namespace network::request
