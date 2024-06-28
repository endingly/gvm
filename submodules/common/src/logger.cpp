#include "logger.hpp"

#include <glog/log_severity.h>
#include <glog/logging.h>

namespace gvm {

void init_log_system() {
  FLAGS_log_dir         = "./logs";
  FLAGS_alsologtostderr = true;
  FLAGS_minloglevel     = google::GLOG_INFO;
  google::InitGoogleLogging(__argv[0]);
}

void log_console(const char* message) { LOG(INFO) << message; }

};  // namespace gvm