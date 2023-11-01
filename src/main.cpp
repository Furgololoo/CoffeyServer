#include <boost/json/src.hpp>
#include <boost/version.hpp>
#include <iostream>

#include "buffer/buffer.h"
#include "database/database.h"
// #include "helpers/json_helper.h"
#include "server/request/request.h"
#include "server/servermanager.h"

int main() {
  if constexpr (BOOST_VERSION < 108200) {
    std::cerr << "Bad Boost Version: " << BOOST_VERSION
              << ", should be 108300 or higher " << std::endl;
    return 1;
  }

  buffer::Buffer &buffer = buffer::Buffer::getInstance();

  std::cout << "max size: " << buffer.maxSize() << std::endl;

  std::unique_ptr<network::request::Request> req1 =
      std::make_unique<network::request::Request>(1);
  std::unique_ptr<network::request::Request> req2 =
      std::make_unique<network::request::Request>(2);
  std::unique_ptr<network::request::Request> req3 =
      std::make_unique<network::request::Request>(3);
  std::unique_ptr<network::request::Request> req4 =
      std::make_unique<network::request::Request>(4);
  std::unique_ptr<network::request::Request> req5 =
      std::make_unique<network::request::Request>(5);
  std::unique_ptr<network::request::Request> req6 =
      std::make_unique<network::request::Request>(6);

  //  buffer.status();
  buffer.add(std::move(req1));
  std::cout << "Buffer size: " << buffer.size()
            << ", is empty: " << buffer.isEmpty() << std::endl;
  //    buffer.status();
  buffer.add(std::move(req2));
  std::cout << "Buffer size: " << buffer.size()
            << ", is empty: " << buffer.isEmpty() << std::endl;
  //    buffer.status();
  buffer.add(std::move(req3));
  std::cout << "Buffer size: " << buffer.size()
            << ", is empty: " << buffer.isEmpty() << std::endl;
  //    buffer.status();
  buffer.add(std::move(req4));
  std::cout << "Buffer size: " << buffer.size()
            << ", is empty: " << buffer.isEmpty() << std::endl;
  //    buffer.status();
  buffer.add(std::move(req5));
  std::cout << "Buffer size: " << buffer.size()
            << ", is empty: " << buffer.isEmpty() << std::endl;
  //    buffer.status();
  buffer.add(std::move(req6));
  std::cout << "Buffer size: " << buffer.size()
            << ", is empty: " << buffer.isEmpty() << std::endl;
  //    buffer.status();

  std::cout << "\nGetting from buffer\n" << std::endl;

  auto val1 = buffer.getNext();
  std::cout << "Buffer size: " << buffer.size()
            << ", is empty: " << buffer.isEmpty() << " "
            << ((val1.has_value()) ? std::to_string(val1.value()->id)
                                   : "nullopt")
            << std::endl;
  auto val2 = buffer.getNext();
  std::cout << "Buffer size: " << buffer.size()
            << ", is empty: " << buffer.isEmpty() << " "
            << ((val2.has_value()) ? std::to_string(val2.value()->id)
                                   : "nullopt")
            << std::endl;
  auto val3 = buffer.getNext();
  std::cout << "Buffer size: " << buffer.size()
            << ", is empty: " << buffer.isEmpty() << " "
            << ((val3.has_value()) ? std::to_string(val3.value()->id)
                                   : "nullopt")
            << std::endl;
  auto val4 = buffer.getNext();
  std::cout << "Buffer size: " << buffer.size()
            << ", is empty: " << buffer.isEmpty() << " "
            << ((val4.has_value()) ? std::to_string(val4.value()->id)
                                   : "nullopt")
            << std::endl;
  auto val5 = buffer.getNext();
  std::cout << "Buffer size: " << buffer.size()
            << ", is empty: " << buffer.isEmpty() << " "
            << ((val5.has_value()) ? std::to_string(val5.value()->id)
                                   : "nullopt")
            << std::endl;
  auto val6 = buffer.getNext();
  std::cout << "Buffer size: " << buffer.size()
            << ", is empty: " << buffer.isEmpty() << " "
            << ((val6.has_value()) ? std::to_string(val6.value()->id)
                                   : "nullopt")
            << std::endl;
  auto val7 = buffer.getNext();
  std::cout << "Buffer size: " << buffer.size()
            << ", is empty: " << buffer.isEmpty() << " "
            << ((val7.has_value()) ? std::to_string(val7.value()->id)
                                   : "nullopt")
            << std::endl;
  auto val8 = buffer.getNext();
  std::cout << "Buffer size: " << buffer.size()
            << ", is empty: " << buffer.isEmpty() << " "
            << ((val8.has_value()) ? std::to_string(val8.value()->id)
                                   : "nullopt")
            << std::endl;

  //  auto val1 = buffer.getNext();
  //  std::cout << "val1: "
  //            << ((val1.has_value()) ? std::to_string(val1.value()->id)
  //                                   : "nullopt")
  //            << std::endl;
  //  auto val2 = buffer.getNext();
  //  std::cout << "val2: "
  //            << ((val2.has_value()) ? std::to_string(val2.value()->id)
  //                                   : "nullopt")
  //            << std::endl;

  //  namespace net = boost::asio;
  //  network::ServerManager
  //  server_manager(net::ip::make_address("127.0.0.1"),
  //                                        9999, 1);

  //  database::Database db;

  //  db.displayUsers();
  //  db.displayTables();

  //  namespace json = boost::json;

  //  json::object content;
  //  json::object usersInfo;
  //  usersInfo["assignee_id"] = 1;
  //  usersInfo["reporter_id"] = 1;
  //  usersInfo["implementer_id"] = 1;
  //  content["users_info"] = usersInfo;
  //
  //  json::object ticketData;
  //  ticketData["title"] = "Fix spawner bug";
  //  ticketData["ticket_type"] = 1;
  //  ticketData["attachments"] = json::array{};
  //  ticketData["links"] = json::array{};
  //  ticketData["ticket_type"] = 1;
  //  ticketData["description"] =
  //      "For some values in initial_ai_number and max_ai_number, after"
  //      " entering spawner game crash with error \"ERROR DIVIDE BY 0\"";
  //  ticketData["acceptance_criteria"] =
  //      "After entering spawner, game shouldn't crash";
  //  ticketData["create_date"] = "05.10.2023";
  //  ticketData["create_time"] = "12:47";
  //  ticketData["update_date"] = "06.10.2023";
  //  ticketData["update_time"] = "15:11";
  //  ticketData["component"] = 8;
  //  ticketData["priority"] = 3;
  //  ticketData["status"] = 6;
  //  content["ticket_data"] = ticketData;
  //
  //  json::object request_data;
  //  request_data["user_id"] = 0;
  //  request_data["token"] = "token1234";
  //  request_data["action"] = 2;
  //  request_data["content_id"] = 1;
  //
  //  json::object body;
  //  body["content"] = content;
  //  body["request_data"] = request_data;
  //
  //  helper::json::pretty_print(std::cout, body);

  //  std::cout << ticket << std::endl;

  return 0;
}