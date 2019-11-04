#pragma once

#include "security/Util.h"
#include <string>
#include <vector>

constexpr auto TIC = 1;
constexpr auto TOC = 2;
constexpr auto DIC = 3;
constexpr auto DOC = 4;
extern dh_key *dh;

class NetUtil {
  public:
    NetUtil();
    static std::string              buildTictoc(int mode);
    static std::string              buildDicdoc(int mode);
    static std::string              lengthToHex(int length);
    static std::vector<std::string> unpackTictoc(std::string msg);
    static std::string              unpackDictoc(std::string msg,std::string ip);
    static int                      lengthToInt(std::string length);
    static char                     intToChar(const int i);
    static int                      charToInt(const char c);
};
