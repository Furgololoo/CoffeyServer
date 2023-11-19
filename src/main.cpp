#include <boost/version.hpp>
#include <iostream>

// #include "buffer/buffer.h"
#include "database/database.h"
// #include "helpers/json_helper.h"
// #include "server/request/request.h"
// #include "server/servermanager.h"

int main() {
  if constexpr (BOOST_VERSION < 108200) {
    std::cerr << "Bad Boost Version: " << BOOST_VERSION
        << ", should be 108300 or higher " << std::endl;
    return 1;
  }

  //  namespace net = boost::asio;
  //  network::ServerManager server_manager(net::ip::make_address("127.0.0.1"),
  //                                        9999, 2);
  //  server_manager.start();

  database::Database db;

  auto users = db.getUsers();
  std::cout << users["status"]<<std::endl;

  auto users_list = users["users_list"].as_array();

  for (const auto &user : users_list) {
    auto user_obj = user.as_object();
    std::cout << user_obj["user_name"].as_string() << " " << user_obj[
          "user_role"].
        as_int64() << " " << user_obj["image_path"].as_string() << std::endl;
  }

  // helper::json::pretty_print(std::cout, db.getUsers());
  // db.changeUserName(3, "Kate");
  // db.displayTables();
  // db.displayUsers();

  return 0;
}
