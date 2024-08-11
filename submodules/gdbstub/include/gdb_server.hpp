#pragma once
#include <boost/circular_buffer.hpp>
#include <vector>

#include "gdb_common.hpp"
#include "gvm_stub.hpp"

namespace gvm::gdb {

/* System functions, supported by all stubs */
int  gdb_main(struct gdb_state *state);
void gdb_sys_init(void);
int  gdb_sys_getc(struct gdb_state *state);
int  gdb_sys_putchar(struct gdb_state *state, int ch);
int  gdb_sys_mem_readb(struct gdb_state *state, Address addr, char *val);
int  gdb_sys_mem_writeb(struct gdb_state *state, Address addr, char val);
int  gdb_sys_continue(struct gdb_state *state);
int  gdb_sys_step(struct gdb_state *state);

/// @brief GDB buffer structure
struct GdbBuffer {
  boost::circular_buffer<char> buffer;
  int32_t                      write_pos;
  int32_t                      read_pos;

  GdbBuffer()
      : buffer(boost::circular_buffer<char>(512)), write_pos(0), read_pos(0) {}
};

/// @brief GDB state structure
struct GdbState {
  int signum;
  Reg regs[GDB_REG_NUM];

  GdbState() = default;
};

/// @brief GDB server class
/// @details This class provides a simple GDB server implementation that can be
/// used to communicate with a GDB client.
class GdbServer {
 private:
  GdbState  state;
  GdbBuffer input;
  GdbBuffer output;

 public:
  GdbServer();
  ~GdbServer() = default;
  /// @brief write data to the output buffer
  /// @param data data to write
  /// @return number of bytes written
  int write_buffer(const std::vector<char> &data);
  /// @brief read data from the input buffer
  /// @return data read
  std::optional<char> read_buffer();
  /// @brief read data from the input buffer
  /// @param count number of bytes to read
  /// @return data read
  std::optional<std::vector<char>> read_buffer(int count);
};

};  // namespace gvm::gdb
