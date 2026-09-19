//
// Created by alex on 9/19/26.
//
#include "../Headers/Base64.h"

#include "../Classes/BinaryValue.h"
#include "../Headers/Binary.h"

static char GetBase64CharFromAlphabet(const int pos) {
    if (pos >= 0 && pos <= 63)
        return BASE64_ALPHABET[pos];

    return '\0';
}

static int GetAlphabetIndexFromBase64Char(const char c) {
    for (int i = 0; i < 64; ++i) {
        if (BASE64_ALPHABET[i] == c) {
            return i;
        }
    }
    return -1;
}

static std::string DecimalTo6BitBinary(int decimal) {
    std::string bin = "000000";
    for (int i = 5; i >= 0; --i) {
        bin[i] = (decimal % 2 == 1) ? '1' : '0';
        decimal /= 2;
    }
    return bin;
}

static int Binary6BitToDecimal(const std::string& bin) {
    int val = 0;
    for (int i = 0; i < 6; ++i) {
        val = val * 2 + (bin[i] - '0');
    }
    return val;
}

std::string EncodeBase64(const std::string& toEncode) {
    std::string result;

    result.reserve(((toEncode.length() + 2) / 3) * 4);

    const std::string& binaryString = EncodeBinaryAsRawString(toEncode, Text, false);
    std::string fetchedPacket = "";
    fetchedPacket.reserve(6);

    for (const char& bit : binaryString) {
        fetchedPacket += bit;
        if (fetchedPacket.length() == 6) {
            int index = Binary6BitToDecimal(fetchedPacket);
            result += GetBase64CharFromAlphabet(index);
            fetchedPacket.clear();
        }
    }

    if (!fetchedPacket.empty()) {
        while (fetchedPacket.length() < 6) {
            fetchedPacket += '0';
        }
        int index = Binary6BitToDecimal(fetchedPacket);
        result += GetBase64CharFromAlphabet(index);
    }

    size_t remainder = toEncode.length() % 3;
    if (remainder == 1) {
        result += "==";
    } else if (remainder == 2) {
        result += '=';
    }

    return result;
}


std::string DecodeBase64(const std::string& toDecode) {
    std::string binaryStream = "";
    binaryStream.reserve(toDecode.length() * 6);

    for (char c : toDecode) {
        if (c == '=') break;

        int index = GetAlphabetIndexFromBase64Char(c);
        if (index != -1) {
            binaryStream += DecimalTo6BitBinary(index);
        }
    }
    std::string decodedResult = "";
    std::string byteBuffer = "";
    byteBuffer.reserve(8);

    for (char bit : binaryStream) {
        byteBuffer += bit;
        if (byteBuffer.length() == 8) {
            std::string charCode = DecodeBinaryFromRawString(byteBuffer, Text);
            decodedResult += charCode;
            byteBuffer.clear();
        }
    }

    return decodedResult;
}