//
// Created by alex on 9/13/26.
//

#ifndef CENCODE_BINARYVALUE_H
#define CENCODE_BINARYVALUE_H
#include <cstdint>
#include <string>
#include <utility>

enum ValueType : uint8_t {
    Decimal,
    Text,
    Unknown
};

class BinaryValue {
private:
    std::string realValue = "0";
    std::string binaryValue = "00000000";
    ValueType valueType = Unknown;
public:
    BinaryValue() {};
    BinaryValue(std::string _binaryValue, const ValueType type) {
        binaryValue = std::move(_binaryValue);
        valueType = type;
    }

    std::string getBinary() const {return binaryValue;}
    ValueType getValueType() const {return valueType;}

    void setBinary(const std::string& binaryNr) {binaryValue = binaryNr;}
    void setValueType(const ValueType& valType) {valueType = valType;}

};

#endif //CENCODE_BINARYVALUE_H