//
// Created by furgololoo on 10/14/23.
//

#include "request.h"
#include <iostream>

namespace network::request {
void Request::processRequest(const json::object &data) {
  // check if request contains every important data
  if (!validateRequest(data)) {
    std::cerr << "Request is invalid\n";
  } else {
    std::cout << "Request is valid\n";
    std::cout << data << std::endl;
  }
}

bool Request::validateRequest(const json::object &data) {
  if (!data.contains("request"))
    return false;

  if (auto requestData = data.at("request").get_object();
      !requestData.contains("type") || !requestData.contains("action"))
    return false;

  if (auto userData = data.at("user").get_object();
      !userData.contains("user_id"))
    return false;
  return true;
}

} // namespace network::request