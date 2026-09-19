//
// Created by alex on 9/19/26.
//
#include "../Headers/Ascii85.h"

#include <cstdint>
#include <pstl/algorithm_impl.h>

std::string EncodeAscii85(const std::string& toEncode) {
    std::string result;
    result.reserve(((result.length() + 3) / 4) * 5);

    size_t i = 0;
    size_t len = toEncode.length();

    while (i < len) {
        size_t bytes_in_chunk = 0;
        uint32_t accumulator = 0;

        for (size_t j = 0; j < 4; ++j) {
            accumulator <<= 8;
            if (i < len) {
                accumulator |= static_cast<unsigned char>(toEncode[i++]);
                bytes_in_chunk++;
            } else {
                accumulator |= 0x00;
            }
        }

        char chunk_chars[5];
        for (int j = 4; j >= 0; --j) {
            chunk_chars[j] = static_cast<char>((accumulator % 85) + 33);
            accumulator /= 85;
        }

        for (size_t j = 0; j < bytes_in_chunk + 1; ++j) {
            result.push_back(chunk_chars[j]);
        }
    }

    return result;
}


std::string DecodeAscii85(const std::string& toDecode) {
    std::string result;
    result.reserve((toDecode.length() * 4) / 5);

    size_t i = 0;
    size_t len = toDecode.length();
    const uint32_t pow85[5] = { 52200625, 614125, 7225, 85, 1 };

    while (i < len) {
        size_t chars_in_chunk = 0;
        uint32_t accumulator = 0;

        for (size_t j = 0; j < 5; ++j) {
            if (i < len) {
                char c = toDecode[i++];
                if (c < 33 || c > 117) {
                    return "Invalid base85 character, aborting.";
                }
                accumulator += static_cast<uint32_t>(c - 33) * pow85[j];
                chars_in_chunk++;
            }
            else {
                accumulator += 84 * pow85[j];
            }
        }

        if (chars_in_chunk < 2) {
            return "Malformed base85 payload.";
        }

        size_t bytes_to_extract = chars_in_chunk - 1;
        for (size_t j = 0; j < bytes_to_extract; j++) {
            unsigned char byte = static_cast<unsigned char>((accumulator >> (24 - (j * 8))) & 0xFF);
            result.push_back(byte);
        }
    }

    return result;
}
