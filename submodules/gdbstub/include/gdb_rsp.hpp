#pragma once
#include <cstdint>

namespace gvm::gdb {

/// @brief Helper class for Gdb Remote Serial Protocol (RSP) communication.
class RspHelper {
 private:
  /* data */
 public:
  RspHelper()  = delete;
  ~RspHelper() = delete;
  /// @brief Generate checksum for RSP packet.
  /// @param data check sum for this data.
  /// @param size size of data.
  /// @return checksum value.
  static int generate_checksum(const char* data, int size);
};

}  // namespace gvm::gdb
