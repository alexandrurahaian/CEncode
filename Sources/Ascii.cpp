//
// Created by alex on 9/20/26.
//
#include <string>
#include "../Headers/Ascii.h"

std::string EncodeAscii(const std::string& toEncode) {
    std::string result;
    result.reserve(toEncode.length() * 4);

    for (const char& c : toEncode) {
        if (!result.empty()) {
            result.push_back(' ');
        }

        auto numericValue = static_cast<unsigned char>(c);
        result.append(std::to_string(numericValue));
    }

    return result;
}
std::string DecodeAscii(const std::string& toDecode) {
    std::string result;
    result.reserve(toDecode.length() / 3);

    std::string currentNumberStr;
    for (size_t i = 0; i <= toDecode.length(); ++i) {
        if (i < toDecode.length() && toDecode[i] != ' ') {
            currentNumberStr.push_back(toDecode[i]);
        }
        else {
            if (!currentNumberStr.empty()) {
                int asciiValue = std::stoi(currentNumberStr);

                result.push_back(static_cast<char>(asciiValue));
                currentNumberStr.clear();
            }
        }
    }

    return result;
}