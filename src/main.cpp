#include <boost/version.hpp>
#include <iostream>
#include <chrono>

// #include <boost/date_time/gregorian/gregorian.hpp>
// #include "buffer/buffer.h"
// #include "database/database.h"
// #include "helpers/json_helper.h"
// #include "server/request/request.h"
#include "server/servermanager.h"


int main() {
  if constexpr (BOOST_VERSION < 108200) {
    std::cerr << "Bad Boost Version: " << BOOST_VERSION
        << ", should be 108300 or higher " << std::endl;
    return 1;
  }

  namespace net = boost::asio;
  network::ServerManager server_manager(net::ip::make_address("127.0.0.1"),
                                        9999, 2);
  server_manager.start();

  // database::Database db;
  // db.changeUserPassword(1, "admin");

  // const std::chrono::year_month_day ymd_today{
  //     std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now())};
  // auto expiration_date_tp = std::chrono::sys_days{ymd_today} +
  //                           std::chrono::days(Login::kTokenValidityDays);
  // const std::string today = std::format("{:%Y-%m-%d}", ymd_today);
  // const std::string expiration_date = std::format("{:%Y-%m-%d}",
  //                                                 std::chrono::year_month_day(
  //                                                     expiration_date_tp));
  //
  // boost::gregorian::date expiration_date_gregorian(
  //     boost::gregorian::from_string(expiration_date));
  // boost::gregorian::date current_date(boost::gregorian::day_clock::local_day());
  //
  // std::cout << boost::gregorian::to_iso_extended_string(current_date) <<
  //     std::endl;
  // std::cout << boost::gregorian::to_iso_extended_string(
  //         current_date + boost::gregorian::date_duration(5)) <<
  //     std::endl;
  //
  // boost::posix_time::ptime currentTime =
  //     boost::posix_time::second_clock::local_time();
  //
  // int hour = currentTime.time_of_day().hours();
  // int minute = currentTime.time_of_day().minutes();
  // int second = currentTime.time_of_day().seconds();
  // std::cout << "Aktualna godzina: " << hour << std::endl;
  // std::cout << "Aktualna minuta: " << minute << std::endl;
  // std::cout << "Aktualna sekunda: " << second + minute * 60 + hour * 3600 <<
  //     std::endl;

  // std::cout << db.generateSalt(32) << std::endl;
  // std::cout << db.generateSalt(32) << std::endl;
  // std::cout << db.generateSalt(32) << std::endl;
  // std::cout << db.generateSalt(32) << std::endl;

  // database::Database db;
  // namespace json = boost::json;
  //
  // json::object project_data{{"project_alias", "TW"},
  //                           {"project_name", "The Warhorn"}};
  // // bool status = db.createProject(project_data);
  //
  // std::string begin_date("14.11.2023");
  // std::array<int, 3> begin_date_int{
  //     std::atoi(begin_date.substr(6, 4).c_str()),
  //     std::atoi(begin_date.substr(3, 2).c_str()),
  //     std::atoi(begin_date.substr(0, 2).c_str())
  // };
  // std::string end_date("04.12.2023");
  // std::array<int, 3> end_date_int{
  //     std::atoi(end_date.substr(6, 4).c_str()),
  //     std::atoi(end_date.substr(3, 2).c_str()),
  //     std::atoi(end_date.substr(0, 2).c_str())
  // };
  //
  // std::chrono::year_month_day ymd_begin(
  //     static_cast<std::chrono::year>(begin_date_int[0]),
  //     static_cast<std::chrono::month>(begin_date_int[1]),
  //     static_cast<std::chrono::day>(begin_date_int[2]));
  // std::chrono::year_month_day ymd_end(
  //     static_cast<std::chrono::year>(end_date_int[0]),
  //     static_cast<std::chrono::month>(end_date_int[1]),
  //     static_cast<std::chrono::day>(end_date_int[2]));
  //
  // const std::chrono::year_month_day ymd_today{
  //     std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now())};
  //
  // const std::string today = std::format("{:%d.%m.%Y}", ymd_today);
  // // std::cout << today << std::endl;
  //
  // std::cout << std::is_same_v< // int->double
  //   decltype(false ? 2.0 : 1), double>;

  // if (status) {
  // auto projects = db.getActiveSprint();
  // helper::json::pretty_print(std::cout, projects);
  // } else {
  // std::cerr << "Problem with creating project\n";
  // }

  // auto ticket = db.getTicket(1);
  // helper::json::pretty_print(std::cout, ticket);

  // if (db.createTicket(content))
  // std::cout << "Ticket added\n";
  // else
  // std::cout << "Cannot add ticket\n";

  // auto users = db.getUsers();
  // std::cout << users["status"]<<std::endl;
  //
  // auto users_list = users["users_list"].as_array();
  //
  // for (const auto &user : users_list) {
  //   auto user_obj = user.as_object();
  //   std::cout << user_obj["user_name"].as_string() << " " << user_obj[
  //         "user_role"].
  //       as_int64() << " " << user_obj["image_path"].as_string() << std::endl;
  // }

  // helper::json::pretty_print(std::cout, db.getUsers());
  // db.changeUserName(3, "Kate");
  // db.displayTables();
  // db.displayUsers();

  return 0;
}
