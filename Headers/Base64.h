//
// Created by alex on 9/19/26.
//

#ifndef CENCODE_BASE64_H
#define CENCODE_BASE64_H

#include <string>
inline constexpr std::string_view BASE64_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string EncodeBase64(const std::string& toEncode);
std::string DecodeBase64(const std::string& toDecode);

#endif //CENCODE_BASE64_H
