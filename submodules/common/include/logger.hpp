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
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin()) {
    return fmt::formatter<std::string>::parse(ctx);
  }
  template <typename FormatContext>
  constexpr auto format(gvm::LogLevel level, FormatContext& ctx) {
    std::string level_str;
    switch (level) {
      case gvm::LogLevel::Debug:
        level_str = fmt::format("{}", "Debug");
        break;
      case gvm::LogLevel::Info:
        level_str = fmt::format("{}", "Info");
        break;
      case gvm::LogLevel::Warning:
        level_str = fmt::format("{}", "Warning");
        break;
      case gvm::LogLevel::Error:
        level_str = fmt::format("{}", "Error");
        break;
      default:
        level_str = fmt::format("{}", "Unknown");
    }
    return fmt::formatter<std::string>::format(level_str, ctx);
  }
};

}  // namespace fmt
