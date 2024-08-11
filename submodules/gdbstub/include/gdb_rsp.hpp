#pragma once
#include <fmt/format.h>

#include <unordered_map>

#include "gdb_common.hpp"

namespace gvm::gdb {

/// @brief Status of message received from gdb client.
enum class RspClientStatus { Ok, NotReceived, Error };

/// @brief Type of message send to gdb client.
enum class RspCommandType { Ok, Error, SendToDebugConsole, Signal };

class GdbRspImp {
 public:
  /// @brief Convert signal number to ASCII character
  /// @param data Signal number
  /// @return ASCII character
  static GdbPacket encode_hex(const ByteSequence &data);
  static GdbPacket encode_hex(const uint8_t *data, int len);
  /// @brief Convert ASCII character to signal number
  /// @param data ASCII character
  /// @return Signal number
  static ByteSequence decode_hex(const GdbPacket &data);
  static ByteSequence decode_hex(const char *data, int len);

  /// @brief Calculate 8-bit checksum of a buffer.
  /// @param data check sum for this data.
  /// @param len length of data.
  /// @return checksum value.
  static int generate_checksum(const char *data, int len);

  /// @brief check status of message received from gdb client.
  /// @param data_start first character of message.
  /// @return `0` if packet acknowledged, `1` otherwise. And `-1` if error
  /// occurred.
  static RspClientStatus get_ack_status(char data_start);

  /// @brief Generate packet with given data.
  /// @param data data to be sent to gdb client.
  /// @param len length of data.
  /// @return packet with data and checksum.
  static GdbPacket gen_packet(const char *data, int len);

 private:
  // used to map signal numbers to ASCII characters
  static std::unordered_map<uint8_t, char> sn2ascii;
  static std::unordered_map<char, uint8_t> ascii2sn;
  GdbRspImp()  = delete;
  ~GdbRspImp() = delete;
};

}  // namespace gvm::gdb

namespace fmt {

template <>
struct formatter<gvm::gdb::RspCommandType> : fmt::formatter<std::string> {
  auto format(gvm::gdb::RspCommandType t,
              format_context          &ctx) const -> format_context::iterator;
};

};  // namespace fmt
