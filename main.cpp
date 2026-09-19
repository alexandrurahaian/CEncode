#include <iostream>
#include <array>
#include <filesystem>
#include <fstream>

#include "Headers/Ascii.h"
#include "Headers/Ascii85.h"
#include "Headers/Binary.h"
#include "Headers/Base64.h"
#include "Headers/Hex.h"
#include "Headers/Morse.h"
#include "Headers/URL.h"

enum class Encoder : uint8_t {
    Binary,
    Base64,
    Ascii85,
    Ascii,
    Hex,
    URL,
    Morse,
    UNKNOWN
};

static std::array<std::pair<std::string, Encoder>, 9> EncoderMap {
    {
        {"binary", Encoder::Binary},
        {"base64", Encoder::Base64},
        {"base16", Encoder::Hex},
        {"base85", Encoder::Ascii85},
        {"ascii85", Encoder::Ascii85},
        {"ascii", Encoder::Ascii},
        {"hex", Encoder::Hex},
        {"url", Encoder::URL},
        {"morse", Encoder::Morse},
    }
};

Encoder GetEncoder(std::string arg) {
    for (const auto& [str, enc] : EncoderMap) {
        if (arg == str) return enc;
    }
    return Encoder::UNKNOWN;
}

// ARGUMENTS STRUCTURE:
// 1st --> encoder: binary/base64/hex/etc.
// 2nd --> encode/decode flag: -d --> decode, -e --> encode
// 3rd --> file path / text to manipulate.
// 4th --> output: console --> prints to console | /file/path.ext --> writes to the file

void HandleEncoder(const Encoder& encoder, std::string flag, std::string text, std::string output, const std::vector<std::string>& args) {
    std::string outputResult, inputText = text;

    std::filesystem::path p(text);

    if (std::filesystem::is_directory(p)) {
        std::cout << "Error: Path is an existing directory, not a file or regular text.\n";
        return;
    }
    else {
        std::ifstream file(text);
        if (file.is_open()) {
            inputText.clear();
            std::string line;
            while (std::getline(file, line)) {
                inputText += line + '\n';
            }
            file.close();
        } else inputText = text;
    }

    // std::cout << inputText << " -- input text" << '\n';

    // BINARY
    if (encoder == Encoder::Binary) {
        ValueType vType = ValueType::Unknown;

        if (args.size() < 5 || (args[4] != "-text" && args[5] != "-decimal")) {
            char vTypeOp;

            std::cout << "What value type is the binary text representing? (d - decimal (ex: 1, 2, 3, etc.) | t - text)\n: ";
            std::cin>>vTypeOp;

            if (vTypeOp == 'd') vType = ValueType::Decimal;
            else if (vTypeOp == 't') vType = ValueType::Text;
            else {
                std::cout << "Invalid type: " << vTypeOp << "! Defaulting to text.\n";
                vType = ValueType::Text;
            }
        }
        else {
            const std::string& arg = args[4];
            vType = (arg == "-text" ? Text : (arg == "-decimal" ? Decimal : Unknown));
        }

        if (flag == "-d") outputResult = DecodeBinaryFromRawString(inputText, vType);
        else if (flag == "-e") outputResult = EncodeBinaryAsRawString(inputText, vType);
    }

    // BASE64
    else if (encoder == Encoder::Base64) {
        if (flag == "-d") outputResult = DecodeBase64(inputText);
        else if (flag == "-e") outputResult = EncodeBase64(inputText);
    }
    //HEX
    else if (encoder == Encoder::Hex) {
        bool addSpace = false;
        if (args.size() >= 5 && (args[4] == "-add-spaces")) addSpace = true;

        if (flag == "-d") outputResult = DecodeHexadecimal(inputText);
        else if (flag == "-e") outputResult = EncodeHexadecimal(inputText, addSpace);
    }
    //BASE85/ASCII85
    else if (encoder == Encoder::Ascii85) {
        if (flag == "-d") outputResult = DecodeAscii85(inputText);
        else if (flag == "-e") outputResult = EncodeAscii85(inputText);
    }
    //URL
    else if (encoder == Encoder::URL) {
        if (flag == "-d") outputResult = DecodeURL(inputText);
        else if (flag == "-e") outputResult = EncodeURL(inputText);
    }
    //MORSE
    else if (encoder == Encoder::Morse) {
        if (flag == "-d") outputResult = DecodeMorse(inputText);
        else if (flag == "-e") outputResult = EncodeMorse(inputText);
    }
    //ASCII
    else if (encoder == Encoder::Ascii) {
        if (flag == "-d") outputResult = DecodeAscii(inputText);
        else if (flag == "-e") outputResult = EncodeAscii(inputText);
    }

    if (output == "console") std::cout << outputResult << std::endl;
    else
    {
        std::filesystem::path p(output);

        if (std::filesystem::is_directory(p)) {
            std::cout << "Error: Path is an existing directory, not a file.\n";
            return;
        }
        if (p.has_parent_path() && !std::filesystem::exists(p.parent_path())) {
            std::cout << "Invalid file path provided: Parent directory does not exist.\n"
                      << "Outputting result to console instead.\n" << outputResult << std::endl;
            return;
        }

        std::ofstream file(output);
        if (!file.is_open()) {
            std::cout << "Could not open file @ path: " << output << '\n';
            return;
        }

        file << outputResult;
        file.close();
    }
}

int main(int argc, char *argv[]) {
    std::vector<std::string> arguments;
    if (argc > 1) {
        arguments = std::vector<std::string>(argv + 1, argv + argc);
    }

    if (argc < 4) {
        std::cout << "Too few arguments, expected 4 arguments:\n[1] encoder: binary/base64/hex\n[2] encode/decode flag (-e/-d)\n[3] text/file to decode/encode\n[4] output (console/file-FILEPATH): where to output, console prints to the terminal, file-FILEPATH writes to the file at the path specified in FILEPATH (replace with file path.)\n";
        return 1;
    }

    Encoder encoder = GetEncoder(arguments[0]);
    if (encoder == Encoder::UNKNOWN) {
        std::cout << "Unknown encoder: " << arguments[0] << "\nPlease provide a valid encoder.\n";
        return 2;
    }

    std::string flag = arguments[1];
    std::string text = arguments[2];
    std::string output = arguments[3];

    HandleEncoder(encoder, flag, text, output, arguments);
    return 0;
}