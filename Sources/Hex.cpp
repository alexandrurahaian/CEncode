//
// Created by alex on 9/19/26.
//
#include "../Headers/Hex.h"
#include <string>

inline unsigned char HexCharToValue(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return '\0';
}

std::string EncodeHexadecimal(const std::string& toEncode, bool addSpaces) {
    std::string result;
    result.reserve(toEncode.length() * 2);

    for (const unsigned char& bit : toEncode) {
        result.push_back(HEX_ALPHABET[(bit >> 4) & 0x0F]);
        result.push_back(HEX_ALPHABET[bit & 0x0F]);
        if (addSpaces) result.push_back(' ');
    }

    return result;
}
std::string DecodeHexadecimal(const std::string& toDecode) {
    std::string result;
    result.reserve((toDecode.length() + 1 )/ 3);

    size_t i = 0;
    while (i < toDecode.length()) {
        if (toDecode[i] == ' ') {
            i++;
            continue;
        }

        if (i + 1 >= toDecode.length()) {
            return result;
        }

        unsigned char high = HexCharToValue(toDecode[i]) << 4;
        unsigned char low = HexCharToValue(toDecode[i + 1]);
        result.push_back(high | low);

        i += 2;
    }

    return result;
}