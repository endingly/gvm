#include <gtest/gtest.h>

#include "bfloat16.hpp"
using namespace gvm;

TEST(Bfloat16Test, TestConvert) {
  bfloat16_t a = static_cast<bfloat16_t>(1.0f);
  float    b = static_cast<float>(a);

  ASSERT_EQ(b, 1.0f);
}

TEST(Bfloat16Test, TestAdd) {
  bfloat16_t a = static_cast<bfloat16_t>(1.0f);
  bfloat16_t b = static_cast<bfloat16_t>(2.0f);
  bfloat16_t c = a + b;
  ASSERT_EQ(c, static_cast<bfloat16_t>(3.0f));
}

TEST(Bfloat16Test, TestSub) {
  bfloat16_t a = static_cast<bfloat16_t>(1.0f);
  bfloat16_t b = static_cast<bfloat16_t>(2.0f);
  bfloat16_t c = a - b;
  ASSERT_EQ(c, static_cast<bfloat16_t>(-1.0f));
}

TEST(Bfloat16Test, TestMul) {
  bfloat16_t a = static_cast<bfloat16_t>(1.0f);
  bfloat16_t b = static_cast<bfloat16_t>(2.0f);
  bfloat16_t c = a * b;
  ASSERT_EQ(c, static_cast<bfloat16_t>(2.0f));
}

TEST(Bfloat16Test, TestDiv) {
  bfloat16_t a = static_cast<bfloat16_t>(1.0f);
  bfloat16_t b = static_cast<bfloat16_t>(2.0f);
  bfloat16_t c = a / b;
  ASSERT_EQ(c, static_cast<bfloat16_t>(0.5f));
}

TEST(Bfloat16Test, TestSImplConvet) {
  bfloat16_t a(1.0f);
  bfloat16_t b(2.0f);
  bfloat16_t c = a + b;
  float    d = static_cast<float>(c);
  ASSERT_EQ(d, 3.0f);
}

TEST(Bfloat16Test, TestFmt) {
  bfloat16_t a(1.0f);
  fmt::println("{}", a);
}