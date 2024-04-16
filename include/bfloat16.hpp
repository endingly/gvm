#pragma once
#include <cmath>
#include <cstdint>
#include <ostream>

namespace gvm {

enum class move_type : uint8_t { truncate, round };

struct bfloat16 {
  uint16_t data;

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
static_assert(std::is_trivial<bfloat16>::value,
              "gvm::bfloat16 is not a trivial type");
static_assert(
    sizeof(bfloat16) == 2 && offsetof(bfloat16, data) == 0,
    "gvm::bfloat16 is not 16 bits or it's members are not headed by data");

inline std::ostream& operator<<(std::ostream& os, const bfloat16& bf) {
  return os << float(bf);
}

inline bfloat16 operator+(bfloat16& other) { return other; }
inline bfloat16 operator-(bfloat16& other) {
  other.data ^= 0x8000;
  return other;
}

inline bfloat16 operator+(bfloat16 a, bfloat16 b) {
  return static_cast<bfloat16>(static_cast<float>(a) + static_cast<float>(b));
}

inline bfloat16 operator-(bfloat16 a, bfloat16 b) {
  return static_cast<bfloat16>(static_cast<float>(a) - static_cast<float>(b));
}

inline bfloat16 operator*(bfloat16 a, bfloat16 b) {
  return static_cast<bfloat16>(static_cast<float>(a) * static_cast<float>(b));
}

inline bfloat16 operator/(bfloat16 a, bfloat16 b) {
  return static_cast<bfloat16>(static_cast<float>(a) / static_cast<float>(b));
}

inline bool operator<(bfloat16 a, bfloat16 b) {
  return static_cast<float>(a) < static_cast<float>(b);
}

inline bool operator>(bfloat16 a, bfloat16 b) {
  return static_cast<float>(a) > static_cast<float>(b);
}

inline bool operator==(bfloat16 a, bfloat16 b) {
  return static_cast<float>(a) == static_cast<float>(b);
}

inline bool     operator<=(bfloat16 a, bfloat16 b) { return !(a > b); }
inline bool     operator>=(bfloat16 a, bfloat16 b) { return !(a < b); }
inline bool     operator!=(bfloat16 a, bfloat16 b) { return !(a == b); }
inline bfloat16 operator+=(bfloat16& a, bfloat16 b) { return a = a + b; }
inline bfloat16 operator-=(bfloat16& a, bfloat16 b) { return a = a - b; }
inline bfloat16 operator*=(bfloat16& a, bfloat16 b) { return a = a * b; }
inline bfloat16 operator/=(bfloat16& a, bfloat16 b) { return a = a / b; }
inline bfloat16 operator++(bfloat16& a) {
  return a = a + static_cast<bfloat16>(1.0f);
}
inline bfloat16 operator--(bfloat16& a) {
  return a = a - static_cast<bfloat16>(1.0f);
}
inline bfloat16 operator++(bfloat16& a, int) {
  bfloat16 origin = a;
  ++a;
  return origin;
}
inline bfloat16 operator--(bfloat16& a, int) {
  bfloat16 origin = a;
  --a;
  return origin;
}

};  // namespace gvm

namespace std {
constexpr bool isinf(gvm::bfloat16 x) {
  return !(~x.data & 0x7f80) && !(x.data & 0x7f);
}

constexpr bool isnan(gvm::bfloat16 x) {
  return !(~x.data & 0x7f80) && +(x.data & 0x7f);
}

constexpr bool iszero(gvm::bfloat16 x) { return !(x.data & 0x7fff); }

inline gvm::bfloat16 sin(gvm::bfloat16 x) {
  return static_cast<gvm::bfloat16>(std::sin(static_cast<float>(x)));
}

inline gvm::bfloat16 cos(gvm::bfloat16 x) {
  return static_cast<gvm::bfloat16>(std::cos(static_cast<float>(x)));
}

inline gvm::bfloat16 real(const gvm::bfloat16& x) { return x; }

};  // namespace std
