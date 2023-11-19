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
      process(std::move(request));
    }
  }
}

void RequestProcessing::process(std::unique_ptr<Request> request) {
  switch (request->getRequestActions()) {
  case ERequestActions::GET:
    get(std::move(request));
    break;
  case ERequestActions::CREATE:
    create(std::move(request));
    break;
  case ERequestActions::UPDATE:
    update(std::move(request));
    break;
  case ERequestActions::REMOVE:
    get(std::move(request));
    break;
  case ERequestActions::CLOSE_SESSION:
    closeSession(std::move(request));
    break;
  default:
    std::cerr << "Bad request action\n";
  }
}

void RequestProcessing::get(std::unique_ptr<Request> request) {}

void RequestProcessing::create(std::unique_ptr<Request> request) {
  //  db.create(request->getContentJson(), request->getContentID());
}

void RequestProcessing::update(std::unique_ptr<Request> request) {}

void RequestProcessing::remove(std::unique_ptr<Request> request) {}

void RequestProcessing::closeSession(std::unique_ptr<Request> request) {
  std::cerr << "Closing session\n";
}

} // namespace network::request