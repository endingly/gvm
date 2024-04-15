#pragma once
#include <cstdint>
#include <ostream>

namespace gvm {

enum class move_type : uint8_t { truncate, round };

struct bfloat16 {
  uint16_t  data;
  move_type move_mode = move_type::truncate;

  bfloat16() = default;
  explicit bfloat16(float f);
  explicit bfloat16(float f, move_type mode);

  operator float() const;
  explicit operator bool() const;

 private:
  static uint16_t float_to_bfloat16(float f);
  static uint16_t truncate_float_to_bfloat16(float f);
};

static_assert(std::is_standard_layout<bfloat16>::value,
              "gvm::bfloat16 is not a standard layout type");
// static_assert(std::is_trivial<bfloat16>::value,
//               "gvm::bfloat16 is not a trivial type");

inline std::ostream& operator<<(std::ostream& os, const bfloat16& bf) {
  return os << float(bf);
}

inline bfloat16 operator+(bfloat16& other) { return other; }
inline bfloat16 operator-(bfloat16& other) {
  other.data ^= 0x8000;
  return other;
}


};  // namespace gvm