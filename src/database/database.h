//
// Created by bfurg on 16/10/2023.
//

#pragma once

#include <boost/json.hpp>
#include <memory>
#include <pqxx/pqxx>

namespace database {
namespace json = boost::json;

class Database {
public:
  Database();

  void connect();
  void displayTables();
  void displayUsers();

  void createUser(const std::string &userName);
  void createTicket(const json::object &data);

private:
  std::unique_ptr<pqxx::connection> conn;
};

} // namespace database
