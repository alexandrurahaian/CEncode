//
// Created by alex on 9/19/26.
//

#ifndef CENCODE_HEX_H
#define CENCODE_HEX_H

#include <string>

inline constexpr std::string_view HEX_ALPHABET = "0123456789ABCDEF";

std::string EncodeHexadecimal(const std::string& toEncode, bool addSpaces = false);
std::string DecodeHexadecimal(const std::string& toDecode);

#endif //CENCODE_HEX_H
