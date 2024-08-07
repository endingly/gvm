#include <gtest/gtest.h>

#include "gdb_rsp.hpp"
#include "logger.hpp"

TEST(GdbRsp, Test_get_ack_status) {
  using namespace gvm::gdb;
  char s = '+';
  EXPECT_EQ(RspHelper::get_ack_status(s), RspClientStatus::Ok);
  s = '-';
  EXPECT_EQ(RspHelper::get_ack_status(s), RspClientStatus::NotReceived);
  s = '0';
  EXPECT_EQ(RspHelper::get_ack_status(s), RspClientStatus::Error);
}