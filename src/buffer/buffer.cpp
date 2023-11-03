//
// Created by bfurg on 31/10/2023.
//

#include "buffer.h"
#include <algorithm>
#include <iostream>

namespace buffer {
Buffer::Buffer() : buffer(std::array<std::unique_ptr<Request>, kBufferSize>{}) {
  toWrite = buffer.begin();
  toRead = buffer.begin();
}

void Buffer::add(std::unique_ptr<Request> request) {
  *toWrite = std::move(request);
  toWrite++;

  if (counter == 0)
    onDataAvailable();
  if (counter < kBufferSize)
    counter++;

  if (toWrite == buffer.end())
    toWrite = buffer.begin();
}

std::optional<std::unique_ptr<Request>> Buffer::getNext() {
  auto value = std::move(*toRead);
  if (value) {
    toRead++;
    counter--;
  } else
    return std::nullopt;

  if (toRead == buffer.end())
    toRead = buffer.begin();
  return value;
}

void Buffer::status() {
  std::cout << "Begin status" << std::endl;
  for (const auto &i : buffer) {
    std::cout << "id: " << ((i) ? &i : nullptr) << std::endl;
  }
  std::cout << "End status" << std::endl;
}

bool Buffer::isEmpty() const { return counter == 0; }

int Buffer::size() const { return counter; }

void Buffer::setOnDataAvailable(std::function<void()> func) {
  onDataAvailable = func;
};
} // namespace buffer