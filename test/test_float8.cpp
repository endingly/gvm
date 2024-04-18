#include <gtest/gtest.h>

#include "float8.hpp"

using float8 = gvm::float_e4m3_t;

TEST(Float8Test, TestFloat8) {
  float8 a(1.0f);
  float8 b(2.0f);
  float8 c = a + b;
  std::cout << c << std::endl;
  ASSERT_EQ(c, 3.0f);
}