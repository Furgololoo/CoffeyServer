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
      m_request = std::move(request);
      process();
    }
  }
}

void RequestProcessing::test() {
  std::cout << "Processing test request" << std::endl;
  helper::json::pretty_print(std::cout, m_request->getRequestDataJson());

  auto request_data = m_request->getRequestDataJson();
  if (request_data.contains("token")) {
    auto user_id = request_data.at("user_id").as_int64();
    if (db.checkToken(user_id, request_data.at("token").as_string().c_str()))
      std::cout << "token is valid" << std::endl;
    else
      std::cout << "token is not valid" << std::endl;
  }
}

void RequestProcessing::process() {
  switch (m_request->getRequestActions()) {
  case ERequestActions::GET:
    get();
    break;
  case ERequestActions::CREATE:
    create();
    break;
  case ERequestActions::UPDATE:
    update();
    break;
  case ERequestActions::REMOVE:
    get();
    break;
  case ERequestActions::CLOSE_SESSION:
    closeSession();
    break;
  case ERequestActions::LOGIN:
    login();
    break;
  case ERequestActions::TEST:
    test();
    break;
  default:
    std::cerr << "Bad request action\n";
  }
}

void RequestProcessing::get() {
  switch (m_request->getContentID()) {
  case EContentID::TICKET:
    break;
  case EContentID::SPRINT:
    break;
  case EContentID::USER:
    break;
  case EContentID::TOKEN:
    break;
  case EContentID::ATTACHMENT:
    break;
  }
}

void RequestProcessing::create() {
  //  db.create(request->getContentJson(), request->getContentID());
}

void RequestProcessing::update() {
}

void RequestProcessing::remove() {
}

void RequestProcessing::closeSession() {
  std::cerr << "Closing session\n";
}

} // namespace network::request
