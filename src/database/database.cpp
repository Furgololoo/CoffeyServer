//
// Created by bfurg on 16/10/2023.
//

#include "database.h"
#include "../utils/config.h"

#include <iostream>

database::Database::Database() {
  connect();
}

void database::Database::connect() {
  try {
    conn = std::make_unique<pqxx::connection>(
        "dbname=CoffeyDB user=postgres password="
        "postgres hostaddr=127.0.0.1 port=5432");

    if (conn->is_open()) {
      std::cout << "Opened database successfully: " << conn->dbname()
          << std::endl;
    } else {
      std::cerr << "Cannot open database" << std::endl;
    }
  } catch (const std::exception &e) {
    std::cerr << "database exception: " << e.what() << std::endl;
  }
}

void database::Database::displayTables() {
  pqxx::work txn(*conn.get());
  pqxx::result result = txn.exec("SELECT table_name "
      "FROM information_schema.tables"
      " WHERE table_type='BASE TABLE' "
      "AND table_schema='public';");

  for (const auto &row : result) {
    std::cout << "Table Name: " << row["table_name"].as<std::string>()
        << std::endl;
  }
  txn.commit();
}

void database::Database::displayUsers() {
  pqxx::work txn(*conn.get());
  pqxx::result result = txn.exec("SELECT * FROM \"User\";");

  for (const auto &row : result) {
    std::cout << "User: " << row["user_id"].as<int>()
        << " name: " << row["user_name"].as<std::string>() << std::endl;
  }
  txn.commit();
}

void database::Database::createTicket(const boost::json::object &data) {
  // const auto query = "INSERT INTO tickets (assignee_id, reporter_id, "
  //                    "implementer_id, title, create_date, create_time, "
  //                    "update_date, update_time, component, priority, status,
  //                    " "other_data, sprint_id)" "VALUES ('" +
  //                    +"');";
  // pqxx::work txn(*conn.get());
}

boost::json::object database::Database::get(const int object_id,
                                            const EContentID content_id) const {
  return boost::json::object();
}

bool database::Database::create(const boost::json::object &data,
                                const EContentID content_id) const {
  switch (content_id) {
  case EContentID::TICKET:
    break;
  case EContentID::SPRINT:
    break;
  case EContentID::USER:
    break;
  case EContentID::ATTACHMENT:
    break;
  default:
    return false;
  }
  return true;
}

bool database::Database::update(const int object_id,
                                const boost::json::object &data,
                                const EContentID content_id) const {
  return false;
}

bool database::Database::remove(const int object_id,
                                const EContentID content_id) const {
  return false;
}

// ############# User management #############
bool database::Database::changeUserName(const int user_id,
                                        const std::string &name) {
  try {
    pqxx::work txn(*conn.get());
    std::string query = "UPDATE \"User\" SET user_name = \'" + name + "\'" +
                        " WHERE user_id = " + std::to_string(user_id) + ";";
    pqxx::result result = txn.exec(query);

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << e.what() << std::endl;
    return false;
  }
  return true;
}

bool database::Database::changeUserRole(const int user_id, const int role) {
  try {
    pqxx::work txn(*conn.get());
    std::string query = "UPDATE \"User\" SET user_role = \'" +
                        std::to_string(role) +
                        "\'" +
                        " WHERE user_id = " + std::to_string(user_id) + ";";
    pqxx::result result = txn.exec(query);

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << e.what() << std::endl;
    return false;
  }
  return true;
}

bool database::Database::changeUserPassword(const int user_id,
                                            const std::string &password) {
  try {
    pqxx::work txn(*conn.get());
    std::string query = "UPDATE \"User\" SET password = \'" + password + "\'" +
                        " WHERE user_id = " + std::to_string(user_id) + ";";
    pqxx::result result = txn.exec(query);

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << e.what() << std::endl;
    return false;
  }
  return true;
}

boost::json::object database::Database::getUsers() {
  json::object users_list_object;
  try {
    pqxx::work txn(*conn.get());
    std::string query =
        "SELECT user_name, user_role, image_path FROM \"User\";";
    pqxx::result result = txn.exec(query);
    json::array users_list{};

    for (const auto &row : result) {
      json::object user;
      user["user_name"] = row["user_name"].as<std::string>();
      user["user_role"] = row["user_role"].as<int>();
      user["image_path"] = row["image_path"].as<std::string>();
      users_list.push_back(user);
    }

    txn.commit();
    users_list_object["users_list"] = users_list;
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << e.what() << std::endl;
    users_list_object["status"] = 1;
    return users_list_object;
  }
  users_list_object["status"] = 0;
  return users_list_object;
}
