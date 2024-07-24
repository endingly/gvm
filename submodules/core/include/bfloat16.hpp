#pragma once
#include <fmt/format.h>

#include <cmath>
#include <cstdint>
#include <ostream>

namespace gvm {

#pragma region bfloat16 definition
enum class move_type : uint8_t { truncate, round };
struct bfloat16_t {
  uint16_t data;

  bfloat16_t() = default;
  explicit bfloat16_t(float f);
  explicit bfloat16_t(float f, move_type mode);

  operator float() const;
  explicit operator bool() const;

 private:
  static uint16_t float_to_bfloat16(float f);
  static uint16_t truncate_float_to_bfloat16(float f);
};
#pragma endregion

#pragma region bfloat16 static asserts
static_assert(std::is_standard_layout<bfloat16_t>::value,
              "gvm::bfloat16 is not a standard layout type");
static_assert(std::is_trivial<bfloat16_t>::value,
              "gvm::bfloat16 is not a trivial type");
static_assert(
    sizeof(bfloat16_t) == 2 && offsetof(bfloat16_t, data) == 0,
    "gvm::bfloat16 is not 16 bits or it's members are not headed by data");
#pragma endregion

#pragma region bfloat16 operators
inline std::ostream& operator<<(std::ostream& os, const bfloat16_t& bf) {
  return os << float(bf);
}

inline bfloat16_t operator+(bfloat16_t& other) { return other; }
inline bfloat16_t operator-(bfloat16_t& other) {
  other.data ^= 0x8000;
  return other;
}

inline bfloat16_t operator+(bfloat16_t a, bfloat16_t b) {
  return static_cast<bfloat16_t>(static_cast<float>(a) + static_cast<float>(b));
}

inline bfloat16_t operator-(bfloat16_t a, bfloat16_t b) {
  return static_cast<bfloat16_t>(static_cast<float>(a) - static_cast<float>(b));
}

inline bfloat16_t operator*(bfloat16_t a, bfloat16_t b) {
  return static_cast<bfloat16_t>(static_cast<float>(a) * static_cast<float>(b));
}

inline bfloat16_t operator/(bfloat16_t a, bfloat16_t b) {
  return static_cast<bfloat16_t>(static_cast<float>(a) / static_cast<float>(b));
}

inline bool operator<(bfloat16_t a, bfloat16_t b) {
  return static_cast<float>(a) < static_cast<float>(b);
}

inline bool operator>(bfloat16_t a, bfloat16_t b) {
  return static_cast<float>(a) > static_cast<float>(b);
}

inline bool operator==(bfloat16_t a, bfloat16_t b) {
  return static_cast<float>(a) == static_cast<float>(b);
}

inline bool     operator<=(bfloat16_t a, bfloat16_t b) { return !(a > b); }
inline bool     operator>=(bfloat16_t a, bfloat16_t b) { return !(a < b); }
inline bool     operator!=(bfloat16_t a, bfloat16_t b) { return !(a == b); }
inline bfloat16_t operator+=(bfloat16_t& a, bfloat16_t b) { return a = a + b; }
inline bfloat16_t operator-=(bfloat16_t& a, bfloat16_t b) { return a = a - b; }
inline bfloat16_t operator*=(bfloat16_t& a, bfloat16_t b) { return a = a * b; }
inline bfloat16_t operator/=(bfloat16_t& a, bfloat16_t b) { return a = a / b; }
inline bfloat16_t operator++(bfloat16_t& a) {
  return a = a + static_cast<bfloat16_t>(1.0f);
}
inline bfloat16_t operator--(bfloat16_t& a) {
  return a = a - static_cast<bfloat16_t>(1.0f);
}
inline bfloat16_t operator++(bfloat16_t& a, int) {
  bfloat16_t origin = a;
  ++a;
  return origin;
}
inline bfloat16_t operator--(bfloat16_t& a, int) {
  bfloat16_t origin = a;
  --a;
  return origin;
}
#pragma endregion

};  // namespace gvm

namespace std {
constexpr bool isinf(gvm::bfloat16_t x) {
  return !(~x.data & 0x7f80) && !(x.data & 0x7f);
}

constexpr bool isnan(gvm::bfloat16_t x) {
  return !(~x.data & 0x7f80) && +(x.data & 0x7f);
}

constexpr bool iszero(gvm::bfloat16_t x) { return !(x.data & 0x7fff); }

inline gvm::bfloat16_t sin(gvm::bfloat16_t x) {
  return static_cast<gvm::bfloat16_t>(std::sin(static_cast<float>(x)));
}

inline gvm::bfloat16_t cos(gvm::bfloat16_t x) {
  return static_cast<gvm::bfloat16_t>(std::cos(static_cast<float>(x)));
}

inline gvm::bfloat16_t real(const gvm::bfloat16_t& x) { return x; }

};  // namespace std

namespace fmt {
template <>
struct formatter<gvm::bfloat16_t> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) {
    return ctx.begin();
  }

  template <typename FormatContext>
  constexpr auto format(const gvm::bfloat16_t& x, FormatContext& ctx) {
    return fmt::format_to(ctx.out(), "{}", float(x));
  }
};
};  // namespace fmt