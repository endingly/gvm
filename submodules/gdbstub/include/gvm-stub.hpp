#pragma once
#include <cstdint>
#include <unordered_map>

namespace gvm::gdb {
using address = uint32_t;

constexpr int GDB_EOF = -1;

/* System functions, supported by all stubs */
int  gdb_main(struct gdb_state *state);
void gdb_sys_init(void);
int  gdb_sys_getc(struct gdb_state *state);
int  gdb_sys_putchar(struct gdb_state *state, int ch);
int  gdb_sys_mem_readb(struct gdb_state *state, address addr, char *val);
int  gdb_sys_mem_writeb(struct gdb_state *state, address addr, char val);
int  gdb_sys_continue(struct gdb_state *state);
int  gdb_sys_step(struct gdb_state *state);

class GdbstubHelper {
 private:
  const static std::unordered_map<int, char> signal_map;

 public:
  GdbstubHelper()  = delete;
  ~GdbstubHelper() = delete;
  static int generate_signal(int signal_num);
};

}  // namespace gvm::gdb
