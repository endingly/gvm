#include <gtest/gtest.h>

#include "gdb_helper.hpp"

template <typename T>
bool operator==(const std::vector<T>& lhs, const std::vector<T>& rhs) {
  for (int i = 0; i < lhs.size(); i++)
    if (lhs[i] != rhs[i]) {
      return false;
    }
  return true;
}

TEST(GdbHelperTest, TestConvetChar) {
  std::vector<uint8_t> number    = {0, 1, 2,  3,  4,  5,  6,  7,
                                    8, 9, 10, 11, 12, 13, 14, 15};
  std::vector<char>    ascii_str = {'0', '1', '2', '3', '4', '5', '6', '7',
                                    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

  auto result_ascii_str = gvm::gdb::GdbstubHelper::encode_hex(number);
  EXPECT_EQ(result_ascii_str.value(), ascii_str);

  auto result_number = gvm::gdb::GdbstubHelper::decode_hex(ascii_str);
  EXPECT_EQ(result_number.value(), number);
}