#include "logger.hpp"

#include <fmt/chrono.h>

#include <fstream>
#include <iostream>

gvm::LogConfig gvm::Logger::config;

namespace gvm {
inline void Logger::write_log(LogLevel level, const std::string& message) {
  std::time_t t = std::time(nullptr);
  auto        s =
      fmt::format("[{:%Y-%m-%d}][{:^7}] {}", fmt::localtime(t), level, message);
  if (config.output_type == LogOutputType::Both ||
      config.output_type == LogOutputType::Console)
    std::cout << s << "\n";
  if (config.output_type == LogOutputType::Both ||
      config.output_type == LogOutputType::File) {
    std::ofstream ofs(config.output_path, std::ios::app);
    ofs << s << "\n";
    ofs.close();
  }
}

void Logger::init_log_system() {
  config = LogConfig();
}

void Logger::init_log_system(const LogConfig& conf) {
  config.level       = conf.level;
  config.output_path = conf.output_path;
  config.output_type = conf.output_type;
}

void Logger::info(const std::string& message) {
  write_log(LogLevel::Info, message);
}

void Logger::debug(const std::string& message) {
#ifdef GVM_DEBUG
  write_log(LogLevel::Debug, message);
#endif
}

void Logger::warning(const std::string& message) {
  write_log(LogLevel::Warning, message);
}

void Logger::error(const std::string& message) {
  write_log(LogLevel::Error, message);
}

};  // namespace gvm