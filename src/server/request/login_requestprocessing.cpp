//
// Created by bfurg on 22/11/2023.
//

#include "requestprocessing.h"
#include <iostream>

namespace network::request {

void RequestProcessing::login() {
  json::object response_data{};
  if (m_request->getContentJson().contains("token")) {
    response_data = tokenLogin();
  } else {
    response_data = passwordLogin();
  }
  m_request->callResponse(response_data);
}

json::object RequestProcessing::tokenLogin() {
  auto token = m_request->getContentJson().at("login").as_string().c_str();
  int user_id = m_request->getContentJson().at("user_id").as_int64();
  json::object response_data{};

  if (db.checkToken(user_id, token)) {
    auto token = database::Database::generateSalt(32);
    db.removeTokenForUser(user_id);
    db.addTokenToUser(user_id, token);
    std::cout << "token is valid" << std::endl;
  } else {
    db.removeTokenForUser(user_id);
    std::cout << "token is not valid" << std::endl;
  }
  return response_data;
}

json::object RequestProcessing::passwordLogin() {
  const std::string login = m_request->getContentJson().at("login").as_string()
                                     .c_str();
  const std::string plain_password = m_request->
                                     getContentJson().at("password").as_string()
                                     .c_str();
  const int user_id = db.getUserId(login);

  const auto current_password = db.getUserPassword(user_id);
  const auto salt = db.getUserSalt(user_id);

  json::object response_data{};

  if (current_password ==
      database::Database::hashPassword(plain_password, salt)) {
    auto token = database::Database::generateSalt(32);
    db.addTokenToUser(user_id, token);
    response_data["token"] = token;
    response_data["user_id"] = user_id;
    auto user_info = db.getUser(user_id);
    response_data["user_name"] = user_info.at("user_name").as_string();
    response_data["user_role"] = user_info.at("user_role").as_int64();
    response_data["image_path"] = user_info.at("image_path").as_string();
  } else {
    response_data["error"] = "Bad login or password";
  }

  return response_data;
}

}
