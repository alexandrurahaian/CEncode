//
// Created by alex on 9/19/26.
//

#ifndef CENCODE_ASCII85_H
#define CENCODE_ASCII85_H

#include <string>

std::string EncodeAscii85(const std::string& toEncode);
std::string DecodeAscii85(const std::string& toDecode);

#endif //CENCODE_ASCII85_H
