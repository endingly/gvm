#include <gtest/gtest.h>

#include <boost/circular_buffer.hpp>

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