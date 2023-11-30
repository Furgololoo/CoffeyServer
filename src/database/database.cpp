//
// Created by bfurg on 16/10/2023.
//

#include "database.h"

#include "../utils/config.h"
#include <openssl/sha.h>
#include <openssl/rand.h>

#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/ptime.hpp>

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

// ############# Project management #############
bool database::Database::createProject(const json::object &data) {
  try {
    pqxx::work txn(*conn.get());
    const std::string query =
        "INSERT INTO \"Project\" (project_alias, project_name) VALUES( $1, $2 );";

    pqxx::result result = txn.exec_params(
        query, data.at("project_alias").as_string().c_str(),
        data.at("project_name").as_string().c_str());

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    return false;
  }
  return true;
}

boost::json::array database::Database::getProjects() {
  json::array projects_list{};
  try {
    pqxx::work txn(*conn.get());
    std::string query =
        "SELECT * FROM \"Project\";";
    pqxx::result result = txn.exec(query);

    for (const auto &row : result) {
      json::object project;
      project["project_id"] = row["project_id"].as<int>();
      project["project_alias"] = row["project_alias"].as<std::string>();
      project["project_name"] = row["project_name"].as<std::string>();
      projects_list.push_back(project);
    }
    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    return projects_list;
  }
  return projects_list;
}

// ############# Sprint management #############

bool database::Database::createSprint(const json::object &data) {

  return false;
}

boost::json::object
database::Database::getSprint(const unsigned int &sprint_id) {
  json::object sprint{};
  try {
    pqxx::work txn(*conn.get());
    std::string query =
        "SELECT * FROM \"Sprint\" WHERE sprint_id = " + std::to_string(
            sprint_id) + ';';
    pqxx::result result = txn.exec(query);

    pqxx::row row = result[0];
    sprint["sprint_name"] = row["sprint_name"].as<std::string>();
    sprint["start_date"] = row["start_date"].as<std::string>();
    sprint["end_date"] = row["end_date"].as<std::string>();

    auto tickets = row["tickets"].as_array();
    sprint["tickets"] = readArray(tickets);

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    return sprint;
  }
  return sprint;
}

boost::json::object database::Database::getActiveSprint() {
  json::object sprint{};
  try {
    pqxx::work txn(*conn.get());
    boost::gregorian::date current_date(
        boost::gregorian::day_clock::local_day());
    const std::string today = boost::gregorian::to_iso_extended_string(
        current_date);
    std::string query =
        "SELECT * FROM \"Sprint\" WHERE start_date <= \'" + today +
        "\' AND end_date >= \'" + today + "\';";
    pqxx::result result = txn.exec(query);

    pqxx::row row = result[0];
    sprint["sprint_name"] = row["sprint_name"].as<std::string>();
    sprint["start_date"] = row["start_date"].as<std::string>();
    sprint["end_date"] = row["end_date"].as<std::string>();

    auto tickets = row["tickets"].as_array();
    sprint["tickets"] = readArray(tickets);

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    return sprint;
  }
  return sprint;
}

// ############# Ticket management #############
bool database::Database::createTicket(const json::object &data) {
  // @formatter:off
  const json::object ticket_data = data.at("ticket_data").as_object();
  const json::object users_info = data.at("users_info").as_object();
  json::object other_data{};
  other_data["description"] = ticket_data.at("description").as_string();
  other_data["acceptance_criteria"] = ticket_data.at("acceptance_criteria").as_string();
  other_data["attachments"] = ticket_data.at("attachments").as_array();
  other_data["links"] = ticket_data.at("links").as_array();
  auto other_data_str = json::serialize(other_data);

  try {
    pqxx::work txn(*conn.get());
  const std::string query =
  "INSERT INTO \"Ticket\" (assignee_id, reporter_id, implementer_id, title, create_date, create_time, update_date, update_time, component, priority, status, other_data, sprint_id)"
  "VALUES( " + std::to_string(users_info.at("assignee_id").to_number<int>()) + ',' + std::to_string(users_info.at("reporter_id").to_number<int>())
  + ',' + std::to_string(users_info.at("implementer_id").to_number<int>()) + ",$1"
  + ",\'" + ticket_data.at("create_date").as_string().c_str() + "\',\'" + ticket_data.at("create_time").as_string().c_str()
  + "\',\'" + ticket_data.at("update_date").as_string().c_str() + "\',\'" + ticket_data.at("update_time").as_string().c_str()
  + "\'," + std::to_string(ticket_data.at("component").to_number<int>()) + ',' + std::to_string(ticket_data.at("priority").to_number<int>())
  + "," + std::to_string(ticket_data.at("status").to_number<int>()) + ",$2," + std::to_string(ticket_data.at("sprint_id").to_number<int>()) + ");";
    // @formatter:on
    pqxx::result result = txn.exec_params(
        query, ticket_data.at("title").as_string().c_str(), other_data_str);

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    return false;
  }
  return true;
}

boost::json::object
database::Database::getTicket(const unsigned int &ticket_id) {
  json::object ticket{};
  json::object users_info{};
  json::object ticket_data{};
  try {
    pqxx::work txn(*conn.get());
    const std::string query =
        "SELECT * FROM \"Ticket\" WHERE ticket_id = "
        + std::to_string(ticket_id) + ";";
    pqxx::result result = txn.exec(query);

    pqxx::row row = result[0];
    users_info["assignee_id"] = row["assignee_id"].as<int>();
    users_info["reporter_id"] = row["reporter_id"].as<int>();
    users_info["implementer_id"] = row["implementer_id"].as<int>();
    ticket["users_info"] = users_info;

    ticket_data["title"] = row["title"].as<std::string>();
    ticket_data["ticket_name"] = row["ticket_name"].as<std::string>();
    ticket_data["create_date"] = row["create_date"].as<std::string>();
    ticket_data["update_date"] = row["update_date"].as<std::string>();
    ticket_data["create_time"] = row["create_time"].as<std::string>();
    ticket_data["update_time"] = row["update_time"].as<std::string>();
    ticket_data["component"] = row["component"].as<int>();
    ticket_data["priority"] = row["priority"].as<int>();
    ticket_data["status"] = row["status"].as<int>();
    ticket_data["sprint_id"] = row["sprint_id"].as<int>();
    ticket_data["other_data"] = boost::json::parse(
        row["other_data"].as<std::string>());
    ticket["ticket_data"] = ticket_data;

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    return ticket;
  }
  return ticket;
}

boost::json::object database::Database::getTicketPreview(
    const unsigned &ticket_id) {
  json::object ticket_preview{};
  try {
    pqxx::work txn(*conn.get());
    const std::string query =
        "SELECT title, ticket_name, priority, update_date, update_time, component, assignee_id, status FROM \"Ticket\" WHERE ticket_id = "
        + std::to_string(ticket_id) + ";";
    pqxx::result result = txn.exec(query);

    pqxx::row row = result[0];

    ticket_preview["title"] = row["title"].as<std::string>();
    ticket_preview["ticket_name"] = row["ticket_name"].as<std::string>();
    ticket_preview["create_date"] = row["create_date"].as<std::string>();
    ticket_preview["create_time"] = row["create_time"].as<std::string>();
    ticket_preview["component"] = row["component"].as<int>();
    ticket_preview["priority"] = row["priority"].as<int>();
    ticket_preview["status"] = row["status"].as<int>();

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    return ticket_preview;
  }
  return ticket_preview;
}

// ############# User management #############
bool database::Database::changeUserName(const unsigned int &user_id,
                                        const std::string &name) {
  try {
    pqxx::work txn(*conn.get());
    std::string query = "UPDATE \"User\" SET user_name = \'" + name + "\'" +
                        " WHERE user_id = " + std::to_string(user_id) + ";";
    pqxx::result result = txn.exec(query);

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << " | " << __FUNCTION__ << e.what() <<
        std::endl;
    return false;
  }
  return true;
}

bool database::Database::changeUserRole(const unsigned int &user_id,
                                        const unsigned int &role) {
  try {
    pqxx::work txn(*conn.get());
    std::string query = "UPDATE \"User\" SET user_role = \'" +
                        std::to_string(role) + "\'" +
                        " WHERE user_id = " + std::to_string(user_id) + ";";
    pqxx::result result = txn.exec(query);

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    return false;
  }
  return true;
}

bool database::Database::changeUserPassword(const unsigned int &user_id,
                                            const std::string &plain_password) {
  std::string salt = generateSalt(32);
  std::string hashed_password = hashPassword(plain_password, salt);
  try {
    pqxx::work txn(*conn.get());
    std::string query = "UPDATE \"User\" SET password = \'" + hashed_password +
                        "\', salt = \'" + salt + "\' WHERE user_id = " +
                        std::to_string(user_id) + ";";
    pqxx::result result = txn.exec(query);

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    return false;
  }
  return true;
}

std::string database::Database::getUserSalt(
    const unsigned int &user_id) {
  std::string salt{};
  try {
    pqxx::work txn(*conn.get());
    std::string query =
        "SELECT salt FROM \"User\" WHERE user_id = "
        + std::to_string(user_id) + ";";
    pqxx::result result = txn.exec(query);
    pqxx::row row = result[0];
    salt = row["salt"].as<std::string>();

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    return salt;
  }
  return salt;
}

std::string database::Database::getUserPassword(
    const unsigned int &user_id) {
  std::string password;
  try {
    pqxx::work txn(*conn.get());
    std::string query =
        "SELECT password FROM \"User\" WHERE user_id = "
        + std::to_string(user_id) + ";";
    pqxx::result result = txn.exec(query);
    pqxx::row row = result[0];
    password = row["password"].as<std::string>();

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    return password;
  }
  return password;
}

boost::json::object database::Database::getUser(const unsigned int &user_id) {
  json::object user{};
  try {
    pqxx::work txn(*conn.get());
    std::string query =
        "SELECT user_name, user_role, image_path FROM \"User\" WHERE user_id = "
        + std::to_string(user_id) + ";";
    pqxx::result result = txn.exec(query);
    pqxx::row row = result[0];
    user["user_name"] = row["user_name"].as<std::string>();
    user["user_role"] = row["user_role"].as<int>();
    user["image_path"] = row["image_path"].as<std::string>();

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    user["status"] = 1;
    return user;
  }
  user["status"] = 0;
  return user;
}

int database::Database::getUserId(const std::string &login) {
  int user_id{};
  try {
    pqxx::work txn(*conn.get());
    std::string query =
        "SELECT user_id FROM \"User\" WHERE login = \'"
        + login + "\';";
    pqxx::result result = txn.exec(query);
    pqxx::row row = result[0];
    user_id = row["user_id"].as<int>();
    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    return -1;
  }
  return user_id;
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
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    users_list_object["status"] = 1;
    return users_list_object;
  }
  users_list_object["status"] = 0;
  return users_list_object;
}

bool database::Database::addTokenToUser(
    const unsigned int user_id,
    const std::string &token_str) {
  boost::gregorian::date expiration_date =
      (boost::gregorian::day_clock::local_day()) +
      boost::gregorian::date_duration(Login::kTokenValidityDays);
  const auto expiration_date_str = boost::gregorian::to_iso_extended_string(
      expiration_date);

  boost::posix_time::ptime current_time =
      boost::posix_time::second_clock::local_time();
  uint32_t expire_time_seconds =
      current_time.time_of_day().seconds() + current_time.time_of_day().
      minutes() * 60 + current_time.time_of_day().hours() * 3600;

  try {
    pqxx::work txn(*conn.get());
    const std::string query =
        "INSERT INTO \"Token\" (user_id, token_value, salt, expiration_date, expiration_time)"
        "VALUES(" + std::to_string(user_id) + ",$1,$2,$3," +
        std::to_string(expire_time_seconds) +
        ");";
    pqxx::result result = txn.exec_params(
        query, token_str, "asddsa", expiration_date_str);

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << " | " << e.what() <<
        std::endl;
    return false;
  }
  return true;
}

bool database::Database::checkToken(const unsigned user_id,
                                    const std::string &token) {
  boost::posix_time::ptime current_time =
      boost::posix_time::second_clock::local_time();
  uint64_t current_time_seconds = current_time.time_of_day().seconds() +
                                  current_time.time_of_day().minutes() * 60 +
                                  current_time.time_of_day().hours() * 3600;
  boost::gregorian::date current_date(boost::gregorian::day_clock::local_day());
  boost::gregorian::date expiration_date{};
  std::string token_value{};
  int expiration_time{};
  try {
    pqxx::work txn(*conn.get());

    std::string query =
        "SELECT token_value, expiration_date, expiration_time FROM \"Token\" WHERE user_id = "
        + std::to_string(user_id) + ";";
    pqxx::result result = txn.exec(query);

    pqxx::row row = result[0];
    token_value = row["token_value"].as<std::string>();
    std::string expiration_date_str = row["expiration_date"].as<std::string>();

    expiration_time = row["expiration_time"].as<uint64_t>();
    expiration_date = boost::gregorian::from_string(expiration_date_str);

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << "\nerror message " << e.
        what() <<
        std::endl;
    return false;
  }
  if ((token == token_value) && (current_date < expiration_date)) {
    return true;
  }
  if ((token == token_value) && (current_date == expiration_date) && (
        current_time_seconds < expiration_time)) {
    return true;
  }
  return false;
}

void database::Database::removeExpiredToken() {
  boost::posix_time::ptime current_time =
      boost::posix_time::second_clock::local_time();
  uint64_t current_time_seconds = current_time.time_of_day().seconds() +
                                  current_time.time_of_day().minutes() * 60 +
                                  current_time.time_of_day().hours() * 3600;
  current_time_seconds += 3600;
  boost::gregorian::date current_date(boost::gregorian::day_clock::local_day());
  try {
    pqxx::work txn(*conn.get());

    std::string query =
        "DELETE FROM \"Token\" WHERE expiration_date > $1 OR (expiration_date = $1 AND "
        + std::to_string(current_time_seconds) + " >= expiration_time);";
    pqxx::result result = txn.exec(query);

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << "\nerror message " << e.
        what() <<
        std::endl;
  }
}

void database::Database::removeTokenForUser(const unsigned user_id) {
  try {
    pqxx::work txn(*conn.get());

    std::string query = "DELETE FROM \"Token\" WHERE user_id = "
                        + std::to_string(user_id) + ";";
    pqxx::result result = txn.exec(query);

    txn.commit();
  } catch (const std::exception &e) {
    std::cerr << "error occured in " << __FUNCTION__ << "\nerror message " << e.
        what() <<
        std::endl;
  }
}

boost::json::array database::Database::readArray(
    pqxx::array_parser &array) {
  json::array json_arr{};
  std::pair<pqxx::array_parser::juncture, std::string> element;
  do {
    element = array.get_next();
    if (element.first == pqxx::array_parser::juncture::string_value)
      json_arr.push_back(element.second.c_str());
  } while (element.first != pqxx::array_parser::juncture::done);
  return json_arr;
}

std::string database::Database::generateSalt(const int length) {
  unsigned char salt[length];
  RAND_bytes(salt, length);

  std::stringstream ss;
  for (int i = 0; i < length; ++i) {
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(
      salt[i]);
  }

  return ss.str();
}

std::string database::Database::hashPassword(const std::string &plain_password,
                                             const std::string &salt) {
  std::string input = plain_password + salt;
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256(reinterpret_cast<const unsigned char *>(input.c_str()), input.length(),
         hash);

  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
    ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash
      [i]);
  }

  return ss.str();
}
