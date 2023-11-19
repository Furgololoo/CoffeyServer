//
// Created by bfurg on 16/10/2023.
//

#pragma once

#include <boost/json.hpp>
#include <memory>
#include <pqxx/pqxx>

#include "../server/request/content_id.h"

namespace database {
namespace json = boost::json;

class Database {
public:
  Database();

  void connect();
  void displayTables();
  void displayUsers();

  void createTicket(const json::object &data);

  // All get operations
  json::object get(const int object_id, const EContentID content_id) const;

  // All create operations
  bool create(const json::object &data, const EContentID content_id) const;

  // All update operations
  bool update(const int object_id, const json::object &data,
              const EContentID content_id) const;

  // All remove operations
  bool remove(const int object_id, const EContentID content_id) const;

  // ############# Ticket management #############

  // ############# User management #############

  bool changeUserName(const int user_id, const std::string &name);
  bool changeUserRole(const int user_id, const int role);
  bool changeUserPassword(const int user_id, const std::string &password);
  json::object getUsers();

private:
  std::unique_ptr<pqxx::connection> conn;
};

} // namespace database
