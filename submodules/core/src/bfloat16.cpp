#include "bfloat16.hpp"

namespace gvm {

uint16_t bfloat16::float_to_bfloat16(float f) {
  uint32_t u = *reinterpret_cast<uint32_t*>(&f);
  if (~u & 0x7f800000)              // Not a finite number
    u += 0x7fff + ((u >> 16) & 1);  // Convert to infinity or NaN
  else if (u & 0xffff)
    u |= 0x10000;  // preserve sign bit
  return uint16_t(u >> 16);
}

uint16_t bfloat16::truncate_float_to_bfloat16(float f) {
  uint32_t u = *reinterpret_cast<uint32_t*>(&f);
  return uint16_t(u >> 16) | (!(~u & 0x7f800000) && (u & 0xffff));
}

bfloat16::bfloat16(float f) : data(float_to_bfloat16(f)) {}

bfloat16::bfloat16(float f, move_type mode) {
  if (mode == move_type::truncate)
    data = truncate_float_to_bfloat16(f);
  else
    data = float_to_bfloat16(f);
}

bfloat16::operator float() const {
  uint32_t u = static_cast<uint32_t>(data) << 16;
  return *reinterpret_cast<float*>(&u);
}

bfloat16::operator bool() const { return data & 0x7fff; }

}  // namespace gvm