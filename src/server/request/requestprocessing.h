//
// Created by bfurg on 03/11/2023.
//

#pragma once

#include "../../buffer/buffer.h"
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
  buffer::Buffer &buffer = buffer::Buffer::getInstance();
};

} // namespace network::request
