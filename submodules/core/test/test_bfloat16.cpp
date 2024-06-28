#include <gtest/gtest.h>

#include "bfloat16.hpp"
using namespace gvm;

TEST(Bfloat16Test, TestConvert) {
  bfloat16 a = static_cast<bfloat16>(1.0f);
  float    b = static_cast<float>(a);

  ASSERT_EQ(b, 1.0f);
}

TEST(Bfloat16Test, TestAdd) {
  bfloat16 a = static_cast<bfloat16>(1.0f);
  bfloat16 b = static_cast<bfloat16>(2.0f);
  bfloat16 c = a + b;
  ASSERT_EQ(c, static_cast<bfloat16>(3.0f));
}

TEST(Bfloat16Test, TestSub) {
  bfloat16 a = static_cast<bfloat16>(1.0f);
  bfloat16 b = static_cast<bfloat16>(2.0f);
  bfloat16 c = a - b;
  ASSERT_EQ(c, static_cast<bfloat16>(-1.0f));
}

TEST(Bfloat16Test, TestMul) {
  bfloat16 a = static_cast<bfloat16>(1.0f);
  bfloat16 b = static_cast<bfloat16>(2.0f);
  bfloat16 c = a * b;
  ASSERT_EQ(c, static_cast<bfloat16>(2.0f));
}

TEST(Bfloat16Test, TestDiv) {
  bfloat16 a = static_cast<bfloat16>(1.0f);
  bfloat16 b = static_cast<bfloat16>(2.0f);
  bfloat16 c = a / b;
  ASSERT_EQ(c, static_cast<bfloat16>(0.5f));
}

TEST(Bfloat16Test, TestSImplConvet) {
  bfloat16 a(1.0f);
  bfloat16 b(2.0f);
  bfloat16 c = a + b;
  float d = static_cast<float>(c);
  ASSERT_EQ(d, 3.0f);
}