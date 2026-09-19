//
// Created by alex on 9/19/26.
//
#include "../Headers/URL.h"
#include "../Headers/Hex.h"

std::string EncodeURL(const std::string& toEncode) {
    std::string result;
    result.reserve(toEncode.length() * 3);

    for (const char& c : toEncode) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            result.push_back(c);
            continue;
        }
        std::string hex = EncodeHexadecimal({c}, false);
        result.push_back('%');
        result.append(hex);
    }

    return result;
}
std::string DecodeURL(const std::string& toDecode) {
    std::string result;
    result.reserve(toDecode.length());

    for (int i = 0; i < toDecode.length(); i++) {
        const char c = toDecode[i];

        if (c == '%') {
            result.append(DecodeHexadecimal(toDecode.substr(i+1, 2)));
            if (i + 2 > toDecode.length()) break;

            i += 2;
        }
        else result.push_back(c);
    }

    return result;
}