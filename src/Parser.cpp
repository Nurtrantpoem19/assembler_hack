#include "Parser.hpp"
#include <fstream>

Parser::Parser(std::optional < std::string asm_file) : p(asm_file)
{
    std::getline(p, currentCommand);
}

void Parser::advance()
{
    while (std::getline(p, currentCommand))
    {

        std::size_t slash = currentCommand.find("//");
        if (slash != std::string::npos)
        {
            currentCommand = currentCommand.substr(0, slash);
        }

        currentCommand.erase(
            std::remove_if(currentCommand.begin(), currentCommand.end(),
                           [](unsigned char ch) { return std::isspace(ch); }),
            currentCommand.end());

        if (!currentCommand.empty())
        {
            return true;
        }
    }
    return false;
};

Parser::CommandType Parser::commandType() const
{
    if (currentCommand.empty())
    {
        return CommandType::Not_Command;
    }

    switch (currentCommand[0])
    {
    case ' ':
    case '\t':
        return CommandType::Not_Command;

    case '/':
        if (currentCommand[1] == '/')
            return CommandType::Not_Command;
        break;

    case '@':
        return CommandType::A_Command;

    case '(':
        return CommandType::L_Command;

    default:
        return CommandType::C_Command;
    }
}

std::string Parser::symbol() const
{
    if (currentCommand[0] == '@')
        return currentCommand.substr(1);

    if (currentCommand.front() == '(' && currentCommand.back() == ')')
        return currentCommand.substr(1, currentCommand.size() - 2);

    return std::nullopt;
}

std::optional<std::string> Parser::dest() const
{
    std::size_t equal_sign = currentCommand.find('=');
    if (equal_sign == std::string::npos)
    {
        return std::nullopt;
    }

    std::string destination = currentCommand.substr(0, equal_sign);
    return destination;
}

std::string Parser::comp() const
{
    std::size_t equal_sign = currentCommand.find('=');
    std::size_t semi_colon = currentCommand.find(';');
    // form : D aka comp, just comp. nothing else
    if (equal_sign == std::string::npos && semi_colon == std::string::npos)
    {
        return currentCommand;
    }
    // form: D = A - 1
    if (equal_sign != std::string::npos && semi_colon == std::string::npos)
    {
        return currentCommand.substr(equal_sign + 1);
    }
    // D;JLT
    if (equal_sign == std::string::npos && semi_colon != std::string::npos)
    {
        return currentCommand.substr(0, semi_colon);
    }
    // D = D - 1 ; JLT
    //
    return currentCommand.substr(equal_sign + 1, semi_colon - equal_sign - 1);
}

std::optional<std::string> jump() const {}
/*
    // dest mnemonic bits: d1 = A, d2 = D, d3 = M
   bool A = destination.find('A') != std::string::npos;
   bool D = destination.find('D') != std::string::npos;
   bool M = destination.find('M') != std::string::npos;

   destination.clear();
   if (A)
       destination.push_back('A');
   if (D)
       destination.push_back('D');
   if (M)
       destination.push_back('M');

*/
