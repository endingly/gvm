#include <gtest/gtest.h>

#include <boost/circular_buffer.hpp>

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

TEST(GdbHelperTest, TestCircularBuffer) {
  boost::circular_buffer<int> buffer(5);
  for (int i = 0; i < 7; i++) {
    buffer.push_back(i);
  }
  // print elements of buffer
  for (int i = 0; i < 5; i++) {
    std::cout << buffer[i] << " ";
  }
  std::cout << std::endl;

  std::vector<int> add_data = {20, 30, 40, 50, 60};

  // new larger buffer
  boost::circular_buffer<int> new_buffer;

  // copy elements from old buffer to new buffer
  new_buffer.assign(10, buffer.begin(), buffer.end());

  // add new data to new buffer
  new_buffer.insert(new_buffer.end(), add_data.begin(), add_data.end());

  // check new buffer
  // 2 3 4 5 6 20 30 40 50 60

  std::vector<int> expected_result = {2, 3, 4, 5, 6, 20, 30, 40, 50, 60};

  // print elements of new buffer
  for (int i = 0; i < 10; i++) {
    std::cout << new_buffer[i] << " ";
  }

  std::cout << std::endl;
  // print expected result
  for (int i = 0; i < expected_result.size(); i++)
    std::cout << expected_result[i] << " ";
  std::cout << std::endl;

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(new_buffer[i], expected_result[i]);
  }
  EXPECT_EQ(new_buffer.size(), 10);
}