#include "gdb_server.hpp"

namespace gvm::gdb {
GdbServer::GdbServer() {
  output = gvm::gdb::GdbBuffer {
    
  };

}

int GdbServer::write_buffer(const std::vector<uint8_t>& data) { 
   
}

};  // namespace gvm::gdb
