#pragma once
#include <fmt/format.h>

#include <cstdint>

#include "logger.hpp"

namespace gvm::gdb {

/// @brief Status of message received from gdb client.
enum class RspClientStatus { Ok, NotReceived, Error };

/// @brief Helper class for Gdb Remote Serial Protocol (RSP) communication.
class RspHelper {
 private:
  /* data */
 public:
  RspHelper()  = delete;
  ~RspHelper() = delete;
  /// @brief Calculate 8-bit checksum of a buffer.
  /// @param data check sum for this data.
  /// @param size size of data.
  /// @return checksum value.
  static int generate_checksum(const char* data, int size);

  /// @brief check status of message received from gdb client.
  /// @param data_start first character of message.
  /// @return `0` if packet acknowledged, `1` otherwise. And `-1` if error
  /// occurred.
  inline static RspClientStatus get_ack_status(char data_start) {
    if (data_start == '+') {
      return RspClientStatus::Ok;
    } else if (data_start == '-') {
      return RspClientStatus::NotReceived;
    }
    Logger::error(
        fmt::format("Received bad packet response: {:#x}", data_start));
    return RspClientStatus::Error;
  }
};

}  // namespace gvm::gdb
