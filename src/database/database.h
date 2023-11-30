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

  // ############# Project management #############
  bool createProject(const json::object &data);
  json::array getProjects();

  // ############# Sprint management #############
  bool createSprint(const json::object &data);
  json::object getSprint(const unsigned int &sprint_id);
  json::object getActiveSprint();

  // ############# Ticket management #############
  bool createTicket(const json::object &data);
  json::object getTicket(const unsigned int &ticket_id);
  json::object getTicketPreview(const unsigned int &ticket_id);

  // ############# User management #############
  bool changeUserName(const unsigned int &user_id, const std::string &name);
  bool changeUserRole(const unsigned int &user_id, const unsigned int &role);
  bool changeUserPassword(const unsigned int &user_id,
                          const std::string &password);
  std::string getUserSalt(const unsigned int &user_id);
  std::string getUserPassword(
      const unsigned int &user_id);
  json::object getUser(const unsigned int &user_id);
  int getUserId(const std::string &login);
  json::object getUsers();

  // ############# Token management #############
  bool addTokenToUser(const unsigned int user_id,
                      const std::string &token_str);
  bool checkToken(const unsigned int user_id, const std::string &token);
  void removeExpiredToken();
  void removeTokenForUser(const unsigned int user_id);

  // ############# Helper #############
  static std::string generateSalt(const int length);
  static std::string hashPassword(const std::string &plain_password,
                                  const std::string &salt);

private:
  static json::array readArray(pqxx::array_parser &array);

  std::unique_ptr<pqxx::connection> conn;
};

} // namespace database
