#include "gdb_server.hpp"

namespace gvm::gdb {

GdbServer::GdbServer() {}

int GdbServer::write_buffer(const std::vector<char>& data) {
  if (data.size() > output.buffer.reserve()) {
    auto tmp      = output.buffer;
    output.buffer = boost::circular_buffer<char>(output.buffer.capacity() * 2);
    // copy old data to new buffer
    output.buffer.assign(tmp.begin(), tmp.end());
    // then add new data
    output.buffer.insert(output.buffer.end(), data.begin(), data.end());
    // free old buffer
    tmp.clear();
  }
  // add new data to buffer
  output.buffer.insert(output.buffer.end(), data.begin(), data.end());
  return data.size();
}

char GdbServer::read_buffer() {
  auto result = input.buffer.front();
  input.buffer.pop_front();
  return result;
}

std::optional<std::vector<char>> GdbServer::read_buffer(int count) {
  if (input.buffer.size() < count) {
    return std::nullopt;
  }
  std::vector<char> result(count);
  result.assign(input.buffer.begin(), input.buffer.begin() + count);
  input.buffer.erase(input.buffer.begin(), input.buffer.begin() + count);
  return result;
}

};  // namespace gvm::gdb
