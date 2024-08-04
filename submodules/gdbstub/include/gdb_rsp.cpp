#include "gdb_rsp.hpp"

namespace gvm::gdb {
int RspHelper::generate_checksum(const char* data, int size) {
  unsigned char csum;
  csum = 0;
  while (size--) {
    csum += *data++;
  }
  return csum;
}
}  // namespace gvm::gdb
