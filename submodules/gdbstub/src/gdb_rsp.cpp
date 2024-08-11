#include "gdb_rsp.hpp"

#include <fmt/format.h>

#include <cstdint>

#include "gdb_common.hpp"
#include "logger.hpp"

namespace gvm::gdb {

using std::vector, std::unordered_map;

unordered_map<uint8_t, char> GdbRspImp::sn2ascii = {
    {0, '0'},  {1, '1'},  {2, '2'},  {3, '3'}, {4, '4'},  {5, '5'},
    {6, '6'},  {7, '7'},  {8, '8'},  {9, '9'}, {10, 'a'}, {11, 'b'},
    {12, 'c'}, {13, 'd'}, {14, 'e'}, {15, 'f'}};
unordered_map<char, uint8_t> GdbRspImp::ascii2sn = {
    {'0', 0},  {'1', 1},  {'2', 2},  {'3', 3}, {'4', 4},  {'5', 5},
    {'6', 6},  {'7', 7},  {'8', 8},  {'9', 9}, {'a', 10}, {'b', 11},
    {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}};

int GdbRspImp::generate_checksum(const char* data, int len) {
  unsigned char csum = 0;
  for (int i = 0; i < len; i++) {
    csum += data[i];
  }
  return csum;
}

RspClientStatus GdbRspImp::get_ack_status(char data_start) {
  if (data_start == '+') {
    return RspClientStatus::Ok;
  } else if (data_start == '-') {
    return RspClientStatus::NotReceived;
  }
  Logger::error(fmt::format("Received bad packet response: {:#x}", data_start));
  return RspClientStatus::Error;
}

GdbPacket GdbRspImp::gen_packet(const char* data, int len) {
  GdbPacket result;
  // add start character
  result.push_back('$');
  // add command type
  for (int i = 0; i < len; i++) {
    result.push_back(data[i]);
  }
  // add checksum start
  result.push_back('#');
  // add checksum
  uint8_t csum = generate_checksum(data, len);
  auto    ch   = encode_hex(&csum, 1);
  result.insert(result.end(), ch.begin(), ch.end());
  return result;
}

GdbPacket GdbRspImp::encode_hex(const ByteSequence& data) {
  GdbPacket result(data.size() * 2);
  for (size_t i = 0; i < data.size(); i++) {
    auto first        = (data[i] >> 4) & 0xf;
    auto second       = data[i] & 0xf;
    result[i * 2]     = sn2ascii[first];
    result[i * 2 + 1] = sn2ascii[second];
  }
  return result;
}

GdbPacket GdbRspImp::encode_hex(const uint8_t* data, int len) {
  GdbPacket result(len * 2);
  for (size_t i = 0; i < len; i++) {
    auto first        = (data[i] >> 4) & 0xf;
    auto second       = data[i] & 0xf;
    result[i * 2]     = sn2ascii[first];
    result[i * 2 + 1] = sn2ascii[second];
  }
  return result;
}

ByteSequence GdbRspImp::decode_hex(const GdbPacket& data) {
  ByteSequence result(data.size() / 2 + 1);
  for (size_t i = 0; i < data.size(); i += 2) {
    auto first    = ascii2sn[data[i]];
    auto second   = ascii2sn[data[i + 1]];
    result[i / 2] = (first << 4) | second;
  }
  return result;
}

ByteSequence GdbRspImp::decode_hex(const char* data, int len) {
  ByteSequence result(len / 2 + 1);
  for (size_t i = 0; i < len; i += 2) {
    auto first    = ascii2sn[data[i]];
    auto second   = ascii2sn[data[i + 1]];
    result[i / 2] = (first << 4) | second;
  }
  return result;
}

}  // namespace gvm::gdb

namespace fmt {

auto fmt::formatter<gvm::gdb::RspCommandType>::format(
    gvm::gdb::RspCommandType t,
    format_context&          ctx) const -> format_context::iterator {
  std::string cmd_str = "";
  switch (t) {
    case gvm::gdb::RspCommandType::Ok:
      cmd_str = "OK";
      break;
    case gvm::gdb::RspCommandType::Error:
      cmd_str = "Error";
      break;
    case gvm::gdb::RspCommandType::SendToDebugConsole:
      cmd_str = "SendToDebugConsole";
      break;
    case gvm::gdb::RspCommandType::Signal:
      cmd_str = "Signal";
      break;
    default:
      cmd_str = "Unknown";
      break;
  }
  return fmt::formatter<std::string>::format(cmd_str, ctx);
}
};  // namespace fmt
