#include <gtest/gtest.h>

#include "type_info.hpp"

TEST(type_info, compiler_to_generate) {
  gvm::type_info_t<int> ti;
  std::cout << ti.size << std::endl;
}