//
// Created by bfurg on 03/11/2023.
//

#include "requestprocessing.h"
#include "../../helpers/json_helper.h"
#include "request.h"

namespace network::request {

void RequestProcessing::startWork(std::stop_token stop_token) {
  if (!stop_token.stop_requested()) {
    auto request_optional = buffer.getNext();
    if (request_optional.has_value()) {
      std::unique_ptr<Request> request = std::move(request_optional.value());
      helper::json::pretty_print(std::cout, request->getContentJson());
    }
  }
}

} // namespace network::request