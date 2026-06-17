#ifndef CODE_HPP
#define CODE_HPP

#include <string>

class Code
{
  public:
    static std::string dest(const std::string &mnemonic);
    static std::string jump(const std::string &mnemonic);
    static std::string comp(const std::string &mnemonic);
};

#endif // CODE_HPP
