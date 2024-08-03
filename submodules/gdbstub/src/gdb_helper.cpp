#include "gdb_helper.hpp"

namespace gvm::gdb {
using std::vector, std::unordered_map, std::optional;

unordered_map<uint8_t, char> GdbstubHelper::sn2ascii = {
    {0, '0'},  {1, '1'},  {2, '2'},  {3, '3'}, {4, '4'},  {5, '5'},
    {6, '6'},  {7, '7'},  {8, '8'},  {9, '9'}, {10, 'a'}, {11, 'b'},
    {12, 'c'}, {13, 'd'}, {14, 'e'}, {15, 'f'}};
unordered_map<char, uint8_t> GdbstubHelper::ascii2sn = {
    {'0', 0},  {'1', 1},  {'2', 2},  {'3', 3}, {'4', 4},  {'5', 5},
    {'6', 6},  {'7', 7},  {'8', 8},  {'9', 9}, {'a', 10}, {'b', 11},
    {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}};

optional<vector<char>> GdbstubHelper::encode_hex(const vector<uint8_t>& data) {
  vector<char> result(data.size());
  for (size_t i = 0; i < data.size(); i++) {
    if (data[i] >= 0 && data[i] <= 15)
      result[i] = sn2ascii[data[i]];
    else
      return std::nullopt;
  }
  return result;
}

optional<vector<uint8_t>> GdbstubHelper::decode_hex(const vector<char>& data) {
  vector<uint8_t> result(data.size());
  for (size_t i = 0; i < data.size(); i++) {
    if (data[i] >= '0' && data[i] <= 'f')
      result[i] = ascii2sn[data[i]];
    else
      return std::nullopt;
  }
  return result;
}
};  // namespace gvm::gdb
