#include <gtest/gtest.h>
#include "logger.hpp"

TEST(LoggerTest, Log) {
    gvm::Logger::init_log_system();
    gvm::Logger::log_console("test log message\n");
}