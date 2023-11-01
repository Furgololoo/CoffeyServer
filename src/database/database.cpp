//
// Created by bfurg on 16/10/2023.
//

#include "database.h"
#include "../utils/config.h"

#include <iostream>

database::Database::Database() { connect(); }

void database::Database::connect() {
  try {
    conn = std::make_unique<pqxx::connection>(
        "dbname=coffeydb user=postgres password="
        "2Zkut1B0$$ hostaddr=127.0.0.1 port=5432");

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
  pqxx::result result = txn.exec("SELECT * FROM users;");

  for (const auto &row : result) {
    //    for (const auto &i : row)
    //      std::cout << i.as<std::string>() << std::endl;
    std::cout << "User: " << row["user_id"].as<int>()
              << "\nname: " << row["user_name"].as<std::string>() << std::endl;
  }
  txn.commit();
}

void database::Database::createUser(const std::string &userName) {
  const auto query = "INSERT INTO users (user_name)"
                     "VALUES ('" +
                     userName + "');";

  pqxx::work txn(*conn.get());

  /* Execute SQL query */
  txn.exec(query);
  txn.commit();
  std::cout << "Records created successfully" << std::endl;
}

void database::Database::createTicket(const boost::json::object &data) {
  //  const auto query = "INSERT INTO tickets (assignee_id, reporter_id, "
  //                     "implementer_id, title, create_date, create_time, "
  //                     "update_date, update_time, component, priority, status,
  //                     " "other_data, sprint_id)" "VALUES ('" +
  //                     +"');";
  pqxx::work txn(*conn.get());
}
