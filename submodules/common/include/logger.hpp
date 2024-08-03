#pragma once
#include <fmt/format.h>

#include <string>
namespace gvm {

enum class LogLevel { Debug, Info, Warning, Error };

enum class LogOutputType { Console, File, Both };

struct LogConfig {
  LogLevel      level       = LogLevel::Info;
  LogOutputType output_type = LogOutputType::Console;
  std::string   output_path = "./test/";
};

class Logger {
 private:
  static LogConfig   config;
  inline static void write_log(LogLevel level, const std::string& message);
  Logger()  = delete;
  ~Logger() = delete;

 public:
  static void init_log_system(const LogConfig& conf);
  static void info(const std::string& message);
  static void debug(const std::string& message);
  static void warning(const std::string& message);
  static void error(const std::string& message);
};

};  // namespace gvm

namespace fmt {

template <>
struct formatter<gvm::LogLevel> : fmt::formatter<std::string> {
  auto format(gvm::LogLevel   level,
              format_context& ctx) const -> format_context::iterator {
    std::string level_str;
    switch (level) {
      case gvm::LogLevel::Debug:
        level_str = "Debug";
        break;
      case gvm::LogLevel::Info:
        level_str = "Info";
        break;
      case gvm::LogLevel::Warning:
        level_str = "Warning";
        break;
      case gvm::LogLevel::Error:
        level_str = "Error";
        break;
      default:
        level_str = "Unknown";
    }
    return fmt::formatter<std::string>::format(level_str, ctx);
  }
};

}  // namespace fmt
