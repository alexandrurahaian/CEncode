//
// Created by alex on 9/19/26.
//
#include "../Headers/Morse.h"

std::string EncodeMorse(const std::string& toEncode) {
    std::string result;
    result.reserve(toEncode.length() * 5);

    for (char c : toEncode) {
        char upperC = std::toupper(static_cast<unsigned char>(c));

        std::string morseStr = "";
        for (const auto& pair : MORSE_ALPHABET) {
            if (pair.first == upperC) {
                morseStr = pair.second;
                break;
            }
        }

        if (morseStr.empty() && upperC != ' ') continue;
        if (!result.empty()) result.push_back(' ');
        if (upperC == ' ') {
            result.push_back('/');
        } else {
            result.append(morseStr);
        }
    }

    return result;
}

static char GetCharFromMorse(const std::string& morse) {
    for (const auto& pair : MORSE_ALPHABET) {
        if (pair.second == morse)
            return pair.first;
    }
    return '?';
}

std::string DecodeMorse(const std::string& toDecode) {
    std::string result;
    result.reserve(toDecode.length() / 2);

    std::string fetchedMorse;
    for (size_t i = 0; i <= toDecode.length(); ++i) {
        if (i < toDecode.length() && toDecode[i] != ' ') {
            fetchedMorse.push_back(toDecode[i]);
        }
        else {
            if (!fetchedMorse.empty()) {
                if (fetchedMorse == "/") {
                    result.push_back(' ');
                } else {
                    result.push_back(GetCharFromMorse(fetchedMorse));
                }
                fetchedMorse.clear();
            }
        }
    }

    return result;
}