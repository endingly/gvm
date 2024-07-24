#pragma once

namespace gvm {

enum class LogLevel { Debug, Info, Warning, Error };

enum class LogOutputType { Console, File };

class Logger {
 public:
  static void init_log_system();
  static void log_console(const char* message);
};

};  // namespace gvm