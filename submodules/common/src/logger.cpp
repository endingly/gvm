#include "logger.hpp"

#include <glog/log_severity.h>
#include <glog/logging.h>

namespace gvm {

void Logger::init_log_system() {
  google::InitGoogleLogging("gvm");
  // FLAGS_log_dir         = "./logs";
  FLAGS_alsologtostderr = true;
  FLAGS_minloglevel     = google::GLOG_INFO;
}

void Logger::log_console(const char* message) { LOG(INFO) << message; }

};  // namespace gvm