#pragma once
#include <cstdint>
#include <optional>
#include <unordered_map>
#include <vector>

namespace gvm::gdb {

/// @brief Helper class for GDB stubs
class GdbstubHelper {
 private:
  // used to map signal numbers to ASCII characters
  static std::unordered_map<uint8_t, char> sn2ascii;
  static std::unordered_map<char, uint8_t> ascii2sn;

 public:
  GdbstubHelper()  = delete;
  ~GdbstubHelper() = delete;
  /// @brief Convert signal number to ASCII character
  /// @param data Signal number
  /// @return ASCII character
  static std::optional<std::vector<char>> encode_hex(
      const std::vector<uint8_t> &data);
  /// @brief Convert ASCII character to signal number
  /// @param data ASCII character
  /// @return Signal number
  static std::optional<std::vector<uint8_t>> decode_hex(
      const std::vector<char> &data);
};

}  // namespace gvm::gdb
