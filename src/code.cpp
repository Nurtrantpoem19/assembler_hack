#include "assembler/code.hpp"
#include <string>
#include <unordered_map>

std::string Code::dest(const std::string &mnemonic)
{
    std::size_t bit = mnemonic.find('A');
    std::string destination = "000";
    if (bit != std::string::npos)
    {
        destination[0] = '1';
    }
    bit = mnemonic.find('D');
    if (bit != std::string::npos)
    {
        destination[1] = '1';
    }

    bit = mnemonic.find('M');
    if (bit != std::string::npos)
    {
        destination[2] = '1';
    }
    return destination;
}
std::string Code::jump(const std::string &mnemonic)
{

    static const std::unordered_map<std::string, std::string> jumpMap = {
        {"JGT", "001"}, {"JEQ", "010"}, {"JGE", "011"}, {"JLT", "100"},
        {"JNE", "101"}, {"JLE", "110"}, {"JMP", "111"}};

    auto it = jumpMap.find(mnemonic);
    if (it != jumpMap.end())
    {
        return it->second;
    }
    return "000";
}
std::string Code::comp(const std::string &mnemonic)
{
    auto it = mnemonic;
    std::size_t pos = it.find("M");
    std::string a_bit = "0";
    if (pos != std::string::npos)
    {
        it[pos] = 'A';

        a_bit = "1";
    }

    std::unordered_map<std::string, std::string> compMap = {
        {"0", "101010"},   {"1", "111111"},   {"-1", "111010"},
        {"D", "001100"},   {"A", "110000"},   {"!D", "001101"},
        {"!A", "110001"},  {"-D", "001111"},  {"-A", "110011"},
        {"D+1", "011111"}, {"A+1", "110111"}, {"D-1", "001110"},
        {"A-1", "110010"}, {"D+A", "000010"}, {"D-A", "010011"},
        {"A-D", "000111"}, {"D&A", "000000"}, {"D|A", "010101"}};
    std::string command = compMap.find(it)->second;
    return a_bit + command;
}

// JGT	001	if out > 0 jump	Jump if the output is Greater Than zero.
// JEQ	010	if out == 0 jump	Jump if the output is EQual to zero.
// JGE	011	if out >= 0 jump	Jump if Greater than or Equal to zero.
// JLT	100	if out < 0 jump	Jump if the output is Less Than zero.
// JNE	101	if out != 0 jump	Jump if Not Equal to zero.
// JLE	110	if out <= 0 jump	Jump if Less than or Equal to zero.
// JMP	111
//
// G
// L
// E
// N
// T
//
// JEQ	010
// JLT	100
// JNE	101
// JLE	110
// JMP	111
