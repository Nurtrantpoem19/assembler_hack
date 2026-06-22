#include "assembler/Assembler.hpp"
#include "assembler/Parser.hpp"
#include "assembler/code.hpp"
#include "assembler/symbolTable.hpp"
#include <algorithm>
#include <bitset>
#include <filesystem>
#include <iostream>
#include <string>

Assembler::Assembler(std::filesystem::path &input,
                     std::filesystem::path &output)
    : table(), parser(input), parser2(input), output_obj(output){};

bool Assembler::isNumber(const std::string &s)
{

    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void Assembler::assemble()
{
    int counter = 0;
    while (parser.advance())
    {
        if (parser.commandType() == Parser::CommandType::L_Command)
        {
            table.addEntry(parser.symbol(), counter);
            continue;
        }
        if (parser.commandType() == Parser::CommandType::A_Command ||
            parser.commandType() == Parser::CommandType::C_Command)
        {
            counter++;
        }
    }

    int variable = 16;
    bool firstLine = true;
    while (parser2.advance())
    {
        if (!firstLine)
        {
            output_obj << std::endl;
        }
        if (parser2.commandType() == Parser::CommandType::A_Command)
        {
            if (isNumber(parser2.symbol()))
            {
                output_obj << "0"
                           << std::bitset<15>(std::stoi(parser2.symbol()));
            }
            else if (table.contains(parser2.symbol()))
            {
                output_obj << "0"
                           << std::bitset<15>(
                                  (table.getAddress(parser2.symbol())));
            }
            else
            {
                table.addEntry(parser2.symbol(), variable);
                output_obj << "0" << std::bitset<15>(variable);
                ++variable;
            }
            continue;
        }

        if (parser2.commandType() == Parser::CommandType::L_Command)
        {
            continue;
        }

        if (parser2.commandType() == Parser::CommandType::C_Command)
        {
            output_obj << "111";

            output_obj << Code::comp(parser2.comp());
            output_obj << Code::dest(parser2.dest());

            output_obj << Code::jump(parser2.jump());
        }
    }

    return;
}
