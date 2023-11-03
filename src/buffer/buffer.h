//
// Created by bfurg on 31/10/2023.
//
#pragma once

#include "../server/request/request.h"
#include "../utils/config.h"
#include <array>
#include <functional>
#include <iterator>
#include <memory>

namespace buffer {

using namespace network::request;
class Buffer {

  explicit Buffer();

public:
  static Buffer &getInstance() {
    static Buffer instance;
    return instance;
  }

  void setOnDataAvailable(std::function<void()> func);

  void add(std::unique_ptr<Request> request);
  std::optional<std::unique_ptr<Request>> getNext();

  void status();
  bool isEmpty() const;
  int size() const;
  int maxSize() const { return static_cast<int>(kBufferSize); }

private:
  std::array<std::unique_ptr<Request>, kBufferSize> buffer;
  std::array<std::unique_ptr<Request>, kBufferSize>::iterator toRead;
  std::array<std::unique_ptr<Request>, kBufferSize>::iterator toWrite;

  int counter = 0;

  std::function<void()> onDataAvailable;
};

} // namespace buffer
