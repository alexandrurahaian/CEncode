//
// Created by alex on 9/19/26.
//

#ifndef CENCODE_MORSE_H
#define CENCODE_MORSE_H

#include <string>
#include <array>

inline constexpr std::array<std::pair<char, std::string_view>, 36> MORSE_ALPHABET =
{{
    {'A', ".-"},
    {'B', "-..."},
    {'C', "-.-."},
    {'D', "-.."},
    {'E', "."},
    {'F', "..-."},
    {'G', "--."},
    {'H', "...."},
    {'I', ".."},
    {'J', ".---"},
    {'K', "-.-"},
    {'L', ".-.."},
    {'M', "--"},
    {'N', "-."},
    {'O', "---"},
    {'P', ".--."},
    {'Q', "--.-"},
    {'R', ".-."},
    {'S', "..."},
    {'T', "-"},
    {'U', "..-"},
    {'V', "...-"},
    {'W', ".--"},
    {'X', "-..-"},
    {'Y', "-.--"},
    {'Z', "--.."},

    {'1', ".----"},
    {'2', "..---"},
    {'3', "...--"},
    {'4', "....-"},
    {'5', "....."},
    {'6', "-...."},
    {'7', "--..."},
    {'8', "---.."},
    {'9', "----."},
    {'0', "-----"}
    }
};

std::string EncodeMorse(const std::string& toEncode);
std::string DecodeMorse(const std::string& toDecode);

#endif //CENCODE_MORSE_H
