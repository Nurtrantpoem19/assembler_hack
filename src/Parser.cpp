#include "assembler/Parser.hpp"
#include <algorithm>
#include <fstream>
#include <optional>

Parser::Parser(std::string asm_file)
{
    p.open(asm_file);
    if (!p.is_open())
    {
        throw std::runtime_error("could not open file " + asm_file + "\n");
    }
    currentCommand = "";
}

bool Parser::advance()
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

    return CommandType::Not_Command;
}

std::string Parser::symbol() const
{
    if (currentCommand[0] == '@')
        return currentCommand.substr(1);

    if (currentCommand.front() == '(' && currentCommand.back() == ')')
        return currentCommand.substr(1, currentCommand.size() - 2);

    return "";
}

std::string Parser::dest() const
{
    std::size_t equal_sign = currentCommand.find('=');
    if (equal_sign == std::string::npos)
    {
        return "";
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

std::string Parser::jump() const
{
    std::size_t semi_colon = currentCommand.find(';');
    if (semi_colon != std::string::npos)
    {
        return currentCommand.substr(semi_colon + 1);
    }
    return "";
}
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
