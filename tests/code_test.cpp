#include "assembler/Parser.hpp"
#include "assembler/code.hpp"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>

#ifndef TEST_FILES
#define TEST_FILES "."
#endif

class codeTest : public ::testing::Test
{
  protected:
    std::filesystem::path base_path = TEST_FILES;
};

TEST_F(codeTest, TestAddasm2)
{
    std::filesystem::path filepath = base_path / "06/Add.asm";
    std::filesystem::path outpath = base_path / "output/Add.hack";
    std::filesystem::create_directories(outpath.parent_path());
    std::ofstream outFile(outpath);

    Parser p(filepath);
    while (p.advance())
    {
        if (p.commandType() == Parser::CommandType::A_Command ||
            p.commandType() == Parser::CommandType::L_Command)
        {
            outFile << "0" << "[15-bit binary of " << p.symbol() << "]\n";
        }
        else if (p.commandType() == Parser::CommandType::C_Command)
        {
            outFile << "111" << Code::comp(p.comp()) << Code::dest(p.dest())
                    << Code::jump(p.jump()) << '\n';
        }
    }
}

TEST_F(codeTest, TestMulasm2)
{

    std::filesystem::path filepath = base_path / "06/Max.asm";
    std::filesystem::path outpath = base_path / "output/Max.hack";
    std::filesystem::create_directories(outpath.parent_path());
    std::ofstream outFile(outpath);

    Parser p(filepath);
    while (p.advance())
    {
        if (p.commandType() == Parser::CommandType::A_Command ||
            p.commandType() == Parser::CommandType::L_Command)
        {
            outFile << "0" << "[15-bit binary of " << p.symbol() << "]\n";
        }
        else if (p.commandType() == Parser::CommandType::C_Command)
        {
            outFile << "111" << Code::comp(p.comp()) << Code::dest(p.dest())
                    << Code::jump(p.jump()) << '\n';
        }
    }
}

TEST_F(codeTest, TestRectasm2)
{

    std::filesystem::path filepath = base_path / "06/Rect.asm";
    std::filesystem::path outpath = base_path / "output/Rect.hack";
    std::filesystem::create_directories(outpath.parent_path());
    std::ofstream outFile(outpath);

    Parser p(filepath);
    while (p.advance())
    {
        if (p.commandType() == Parser::CommandType::A_Command ||
            p.commandType() == Parser::CommandType::L_Command)
        {
            outFile << "0" << "[15-bit binary of " << p.symbol() << "]\n";
        }
        else if (p.commandType() == Parser::CommandType::C_Command)
        {
            outFile << "111" << Code::comp(p.comp()) << Code::dest(p.dest())
                    << Code::jump(p.jump()) << '\n';
        }
    }
}
