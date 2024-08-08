#pragma once
#include <cstdint>
#include <vector>

namespace gvm::gdb {

using Address      = uint32_t;
using Reg          = uint32_t;
using GdbPackage   = std::vector<char>;
using ByteSequence = std::vector<uint8_t>;

}  // namespace gvm::gdb
