#include <gtest/gtest.h>

#include "logger.hpp"

TEST(LoggerTest, LogLevelFmt) { fmt::println("{}", gvm::LogLevel::Info); }

TEST(LoggerTest, LogPrint) {
  gvm::LogConfig config = gvm::LogConfig();
  config.output_path    = "./logs/";
  config.output_type    = gvm::LogOutputType::Both;
  gvm::Logger::init_log_system(config);
  gvm::Logger::info("This is an info message");
  gvm::Logger::debug("This is a debug message");
  gvm::Logger::warning("This is a warning message");
  gvm::Logger::error("This is an error message");
}