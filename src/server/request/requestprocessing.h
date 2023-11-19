//
// Created by bfurg on 03/11/2023.
//

#pragma once

#include "../../buffer/buffer.h"
#include "../../database/database.h"
#include "content_id.h"
#include "requestactions.h"

#include <boost/json.hpp>
#include <functional>
#include <iostream>
#include <stop_token>

namespace network::request {

class RequestProcessing {
public:
  void startWork(std::stop_token stop_token);

private:
  void process(std::unique_ptr<Request> request);

  void get(std::unique_ptr<Request> request);
  void create(std::unique_ptr<Request> request);
  void update(std::unique_ptr<Request> request);
  void remove(std::unique_ptr<Request> request);
  void closeSession(std::unique_ptr<Request> request);

  buffer::Buffer &buffer = buffer::Buffer::getInstance();
  //  database::Database db;
};

} // namespace network::request
