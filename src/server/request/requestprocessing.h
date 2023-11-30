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
  void process();

  void get();
  void create();
  void update();
  void remove();
  void closeSession();

  // login, signup, change user data etc
  void login();

  json::object tokenLogin();
  json::object passwordLogin();


  // only for test
  void test();

  buffer::Buffer &buffer = buffer::Buffer::getInstance();
  database::Database db;

  std::unique_ptr<Request> m_request;
};

} // namespace network::request
