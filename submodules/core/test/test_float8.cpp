#include <gtest/gtest.h>
#include <fmt/core.h>
#include "float8.hpp"

using float8_t = gvm::float_e4m3_t;

TEST(Float8Test, TestFloat8) {
  auto   d = 0xf9;
  int8_t s = *(reinterpret_cast<int8_t*>(&d));
  fmt::println("s: {}", s);
}

TEST(Float8Test, TestFloat8FmtPrint) {
  auto f = float8_t::from_float(1.23456789);
  fmt::print("{:.8f}\n", f);
}