//
// Created by alex on 9/13/26.
//

#ifndef CENCODE_BINARY_H
#define CENCODE_BINARY_H

#include "../Classes/BinaryValue.h"
#include <vector>

void PadBinary(std::string& value);

std::vector<BinaryValue> GetBinaryValuesFromBinaryText(const std::string& binaryText, const ValueType& valType = Text);
std::vector<BinaryValue> EncodeBinary(const std::string& value,const ValueType& valType = Text);
std::string EncodeBinaryAsRawString(const std::string& rawStr, const ValueType& valType = Text, bool delimitWithSpaces = true);
std::string DecodeBinary(const std::vector<BinaryValue>& values);
std::string DecodeBinaryFromRawString(const std::string& rawStr, const ValueType& valType = Text);

BinaryValue EncodeBinaryChar(const char& character);

#endif //CENCODE_BINARY_H
