//
// Created by alex on 9/13/26.
//
#include <iostream>
#include <string>
#include <vector>

#include "../Classes/BinaryValue.h"
#include "../Headers/Binary.h"

void PadBinary(std::string& value) {
    if (value.size() < 8) {
        value.insert(0, 8 - value.size(), '0');
    }
}

BinaryValue GetBinaryFromNumber(unsigned int number) {
    BinaryValue value;
    if (number == 0) {
        value.setBinary("00000000");
        return value;
    }

    std::string binaryValue;
    while (number > 0) {
        binaryValue.insert(0, 1, (number % 2) ? '1' : '0');
        number /= 2;
    }

    PadBinary(binaryValue);
    value.setBinary(binaryValue);
    return value;
}

std::vector<BinaryValue> EncodeBinary(const std::string& value, const ValueType& valType) {
    std::vector<BinaryValue> convertedBinary;

    for (const char& bit : value) {
        BinaryValue bn;
        if (valType == ValueType::Text) {
            bn = GetBinaryFromNumber(static_cast<unsigned char>(bit));
        } else if (valType == ValueType::Decimal) {
            bn = GetBinaryFromNumber(bit - '0');
        }
        bn.setValueType(valType);
        convertedBinary.emplace_back(bn);
    }

    return convertedBinary;
}

std::string DecodeBinary(const std::vector<BinaryValue>& values) {
    std::string result;
    ValueType prevType = ValueType::Text;
    bool hasPrevious = false;

    auto convertDecimal = [&result, &prevType, &hasPrevious](const BinaryValue& val) {
        std::string binaryVal = val.getBinary();
        int decimalVal = 0;
        for (char bit : binaryVal) {
            decimalVal <<= 1;
            decimalVal |= (bit - '0');
        }

        if (hasPrevious) {
            result += ' ';
        }

        result += std::to_string(decimalVal);
        prevType = ValueType::Decimal;
        hasPrevious = true;
    };

    auto convertText = [&result, &prevType, &hasPrevious](const BinaryValue& val) {
        std::string binaryVal = val.getBinary();
        char currentByte = 0;

        if (hasPrevious && prevType == ValueType::Decimal) {
            result += ' ';
        }

        for (char i : binaryVal) {
            currentByte <<= 1;
            currentByte |= (i - '0');
        }

        result += currentByte;
        prevType = ValueType::Text;
        hasPrevious = true;
    };

    for (const BinaryValue& value : values) {
        if (value.getValueType() == ValueType::Text)
            convertText(value);
        else if (value.getValueType() == ValueType::Decimal)
            convertDecimal(value);
    }

    return result;
}

static std::string JoinBinaryVector(const std::vector<BinaryValue>& vctr, const bool delimitWithSpaces = true) {
    std::string result;
    bool isFirst = true;

    for (const BinaryValue& bValue : vctr) {
        if (!isFirst && delimitWithSpaces) {
            result += ' ';
        }
        result += bValue.getBinary();
        isFirst = false;
    }

    return result;
}

std::vector<BinaryValue> GetBinaryValuesFromBinaryText(const std::string& binaryText, const ValueType& valType) {
    std::vector<BinaryValue> convertedBinary;
    std::string binaryValue;

    for (const char& bit : binaryText) {
        if (bit == ' ' && !binaryValue.empty()) {
            BinaryValue bn;
            bn.setBinary(binaryValue);
            bn.setValueType(valType);
            convertedBinary.emplace_back(bn);
            binaryValue.clear();
            continue;
        }
        if (bit != ' ') {
            binaryValue += bit;
        }
    }

    if (!binaryValue.empty()) {
        BinaryValue bn;
        bn.setBinary(binaryValue);
        bn.setValueType(valType);
        convertedBinary.emplace_back(bn);
    }

    return convertedBinary;
}

std::string DecodeBinaryFromRawString(const std::string& rawStr, const ValueType& valType) {
    const std::vector<BinaryValue>& binary = GetBinaryValuesFromBinaryText(rawStr, valType);
    return DecodeBinary(binary);
}

std::string EncodeBinaryAsRawString(const std::string& rawStr, const ValueType& valType, const bool delimitWithSpaces) {
    const std::vector<BinaryValue>& binary = EncodeBinary(rawStr, valType);
    return JoinBinaryVector(binary, delimitWithSpaces);
}

BinaryValue EncodeBinaryChar(const char& character) {
    BinaryValue bn = GetBinaryFromNumber(static_cast<unsigned char>(character));
    bn.setValueType(ValueType::Text);
    return bn;
}