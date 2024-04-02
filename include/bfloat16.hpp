#pragma once
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <elfio.hpp>

struct bfloat16 {
  uint16_t data;
  enum truncate_t { truncate };

  
};
