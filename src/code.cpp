#include "code.hpp"
#include <string>

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
    std::string jump = "000";
    if (mnemonic.find('G') != std::string::npos)
    {
        jump[2] = "1";
        if (mnemonic.find('E') != std::string::npos)
        {
            jump[1] = "1";
        }
        return jump;
    }
    else if (mnemonic.find('L') != std::string::npos)
    {
        jump[0] = "1";
        if (mnemonic.find('E') != std::string::npos)
        {
            jump[1] = "j";
        }
        return jump;
    }
    else if (mnemonic[1] == "E")
    {
        jump[1] = "1";
        return jump;
    }
    else
    {
        if (mnemonic[1] == "N")
        {
            return "101";
        }
        return "111";
    }
}
std::string Code::comp(const std::string &mnemonic);

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
