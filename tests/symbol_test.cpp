#include "assembler/Parser.hpp"
#include "assembler/symbolTable.hpp"
#include "gtest/gtest.h"
#include <filesystem>
#include <fstream>

#ifndef TEST_FILES
#define TEST_FILES "."
#endif

class Symbol_test : public ::testing::Test
{
  protected:
    std::filesystem::path basepath = TEST_FILES;
};

TEST_F(Symbol_test, TestMaxSymbols)
{
    std::filesystem::path filepath = basepath / "06/Max.asm";
    std::filesystem::path outDir = basepath / "output";
    std::filesystem::create_directories(
        outDir); // Fix 1: Ensure directory exists

    SymbolTable table;
    Parser p(filepath.string());
    std::ofstream output(outDir / "MaxSymbols.asm");

    int counter = 0;
    while (p.advance())
    {
        if (p.commandType() == Parser::CommandType::L_Command)
        {
            table.addEntry(p.symbol(), counter);
            continue;
        }

        if (p.commandType() == Parser::CommandType::A_Command ||
            p.commandType() == Parser::CommandType::C_Command)
        {
            counter++;
        }
    }

    Parser p2(filepath.string());
    while (p2.advance())
    {
        if (p2.commandType() == Parser::CommandType::A_Command)
        {
            // Fix 2: Handle both user-defined symbols and raw numeric
            // constants/variables safely
            if (table.contains(p2.symbol()))
            {
                output << "@" << table.getAddress(p2.symbol()) << std::endl;
            }
            else
            {
                output << "@" << p2.symbol() << std::endl;
            }
            continue;
        }

        if (p2.commandType() == Parser::CommandType::L_Command)
        {
            continue;
        }

        // Fix 3: Proper formatting for Hack C-instructions
        if (p2.commandType() == Parser::CommandType::C_Command)
        {
            if (!p2.dest().empty())
                output << p2.dest() << "=";
            output << p2.comp();
            if (!p2.jump().empty())
                output << ";" << p2.jump();
            output << std::endl;
        }
    }
}
