#include <boost/json/src.hpp>
#include <boost/version.hpp>
#include <iostream>

#include "database/database.h"
#include "server/request/request.h"
#include "server/servermanager.h"

int main() {
  if constexpr (BOOST_VERSION < 108200) {
    std::cerr << "Bad Boost Version: " << BOOST_VERSION
              << ", should be 108300 or higher " << std::endl;
    return 1;
  }

  //  namespace net = boost::asio;
  //  network::ServerManager server_manager(net::ip::make_address("127.0.0.1"),
  //                                        9999, 1);

  //  database::Database db;

  //  db.displayUsers();
  //  db.displayTables();

  namespace json = boost::json;

  json::object body;
  json::object usersInfo;
  usersInfo["assignee_id"] = 1;
  usersInfo["reporter_id"] = 1;
  usersInfo["implementer_id"] = 1;
  body["users_info"] = usersInfo;

  json::object ticketData;
  ticketData["title"] = "Fix spawner bug";
  ticketData["description"] =
      "For some values in initial_ai_number and max_ai_number, after entering "
      "spawner game crash with error \"ERROR DIVIDE BY 0\"";
  ticketData["acceptance_criteria"] =
      "After entering spawner, game shouldn't crash";
  ticketData["create_date"] = "2023:10:05";
  ticketData["create_time"] = "12:47";
  ticketData["update_date"] = "2023:10:06";
  ticketData["update_time"] = "15:11";
  ticketData["component"] = 8;
  ticketData["priority"] = 3;
  ticketData["status"] = 6;
  body["ticket_data"] = ticketData;

  json::object ticket;
  ticket["ticket"] = body;

  std::cout << ticket << std::endl;
  
  return 0;
}