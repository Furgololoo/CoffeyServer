//
// Created by furgololoo on 10/14/23.
//

#include "request.h"

#include "../../helpers/json_helper.h"

#include <iostream>

namespace network::request {
Request::Request(const json::object &data) {
  content = data.at("content").get_object();
  helper::json::pretty_print(std::cout, data);
  // auto ticket_data = content.at("ticket_data").as_object();

  request_data = data.at("request_data").as_object();
  content_id =
      static_cast<EContentID>(request_data.at("content_id").as_int64());
  action = static_cast<ERequestActions>(request_data.at("action").as_int64());
  // token = request_data.at("token").as_string();
  // user_id = request_data.at("user_id").as_int64();
}

void Request::setResponse(std::function<void(const std::string &)> response_) {
  response = response_;
}

void Request::callResponse(const json::object &data) const {
  json::object body{{"content", data}};
  json::object request_data{{"content_id", static_cast<int>(content_id)},
                            {"action", static_cast<int>(action)}};
  body["request_data"] = request_data;
  std::cout << "Calling response with data: \n";
  helper::json::pretty_print(std::cout, body);

  response(json::serialize(body));
}

json::object Request::getContentJson() const { return content; }

json::object Request::getRequestDataJson() const {
  return request_data;
}

ERequestActions Request::getRequestActions() const { return action; }
EContentID Request::getContentID() const { return content_id; }

// void Request::processRequest(const json::object &data) {
//   // check if request contains every important data
//   if (!validateRequest(data)) {
//     std::cerr << "Request is invalid\n";
//   } else {
//     std::cout << "Request is valid\n";
//     std::cout << data << std::endl;
//   }
// }
//
// bool Request::validateRequest(const json::object &data) {
//   if (!data.contains("request"))
//     return false;
//
//   if (auto requestData = data.at("request").get_object();
//       !requestData.contains("type") || !requestData.contains("action"))
//     return false;
//
//   if (auto userData = data.at("user").get_object();
//       !userData.contains("user_id"))
//     return false;
//   return true;
// }

} // namespace network::request
