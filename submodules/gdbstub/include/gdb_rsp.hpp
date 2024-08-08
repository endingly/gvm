#pragma once
#include <fmt/format.h>

#include <optional>
#include <unordered_map>

#include "gdb_common.hpp"

namespace gvm::gdb {

/// @brief Status of message received from gdb client.
enum class RspClientStatus { Ok, NotReceived, Error };

class GdbRspImp {
 private:
  /// @brief Convert signal number to ASCII character
  /// @param data Signal number
  /// @return ASCII character
  static std::optional<GdbPackage> encode_hex(const ByteSequence &data);
  /// @brief Convert ASCII character to signal number
  /// @param data ASCII character
  /// @return Signal number
  static std::optional<ByteSequence> decode_hex(const GdbPackage &data);

  /// @brief Calculate 8-bit checksum of a buffer.
  /// @param data check sum for this data.
  /// @return checksum value.
  static int generate_checksum(const GdbPackage &data);

  /// @brief check status of message received from gdb client.
  /// @param data_start first character of message.
  /// @return `0` if packet acknowledged, `1` otherwise. And `-1` if error
  /// occurred.
  static RspClientStatus get_ack_status(char data_start);

 public:
  GdbRspImp()  = default;
  ~GdbRspImp() = default;

 private:
  // used to map signal numbers to ASCII characters
  static std::unordered_map<uint8_t, char> sn2ascii;
  static std::unordered_map<char, uint8_t> ascii2sn;
};

}  // namespace gvm::gdb
