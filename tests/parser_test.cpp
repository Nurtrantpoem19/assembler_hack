#include "assembler/Parser.hpp"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

#ifndef TEST_FILES
#define TEST_FILES "."
#endif
// unit testing for parser.cpp
//
//
//
class ParserTest : public ::testing::Test
{
  protected:
    std::filesystem::path base_path = TEST_FILES;
};

TEST_F(ParserTest, TestAddasm)
{

    std::filesystem::path filepath = base_path / "06/Add.asm";
    Parser parser(filepath.string());

    std::cout << "loading test file from: " << filepath << "\n";

    // @2
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::A_Command);
    EXPECT_EQ(parser.symbol(), "2");

    // D=A
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::C_Command);
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "A");
    EXPECT_EQ(parser.jump(), "");

    // @3
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::A_Command);
    EXPECT_EQ(parser.symbol(), "3");

    // D=D+A
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::C_Command);
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "D+A");
    EXPECT_EQ(parser.jump(), "");

    // @0
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::A_Command);
    EXPECT_EQ(parser.symbol(), "0");

    // M=D
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::C_Command);
    EXPECT_EQ(parser.dest(), "M");
    EXPECT_EQ(parser.comp(), "D");
    EXPECT_EQ(parser.jump(), "");

    // End of file
    EXPECT_FALSE(parser.advance());
}
// =========================================================================
// 2. MAX.ASM TEST (Includes Labels and Symbols)
// =========================================================================
TEST_F(ParserTest, TestMaxAsm)
{
    std::filesystem::path filepath = base_path / "06/Max.asm";
    Parser parser(filepath.string());

    // @R0
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::A_Command);
    EXPECT_EQ(parser.symbol(), "R0");

    // D=M
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "M");

    // @R1
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "R1");

    // D=D-M
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "D-M");

    // @ITSR0
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "ITSR0");

    // D;JGT
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::C_Command);
    EXPECT_EQ(parser.dest(), "");
    EXPECT_EQ(parser.comp(), "D");
    EXPECT_EQ(parser.jump(), "JGT");

    // @R1
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "R1");

    // D=M
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "M");

    // @OUTPUT_D
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "OUTPUT_D");

    // 0;JMP
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "");
    EXPECT_EQ(parser.comp(), "0");
    EXPECT_EQ(parser.jump(), "JMP");

    // (ITSR0) - Label Command
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::L_Command);
    EXPECT_EQ(parser.symbol(), "ITSR0");

    // @R0
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "R0");

    // D=M
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.comp(), "M");

    // (OUTPUT_D) - Label Command
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::L_Command);
    EXPECT_EQ(parser.symbol(), "OUTPUT_D");

    // @R2
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "R2");

    // M=D
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "M");
    EXPECT_EQ(parser.comp(), "D");

    // (END)
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::L_Command);
    EXPECT_EQ(parser.symbol(), "END");

    // @END
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "END");

    // 0;JMP
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.jump(), "JMP");

    EXPECT_FALSE(parser.advance());
}
// =========================================================================
// 3. MAXL.ASM TEST (Symbol-less version)
// =========================================================================
TEST_F(ParserTest, TestMaxLAsm)
{
    std::filesystem::path filepath = base_path / "06/MaxL.asm";
    Parser parser(filepath.string());

    // @0
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::A_Command);
    EXPECT_EQ(parser.symbol(), "0");

    // D=M
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "M");

    // @1
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "1");

    // D=D-M
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.comp(), "D-M");

    // @10
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "10");

    // D;JGT
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.jump(), "JGT");

    // @1
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "1");

    // D=M
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "D");

    // @12
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "12");

    // 0;JMP
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.comp(), "0");
    EXPECT_EQ(parser.jump(), "JMP");

    // @0
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "0");

    // D=M
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.comp(), "M");

    // @2
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "2");

    // M=D
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "M");

    // @14
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "14");

    // 0;JMP
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.jump(), "JMP");

    EXPECT_FALSE(parser.advance());
}
// =========================================================================
// 4. RECT.ASM TEST (Includes Multi-Register Destinations)
// =========================================================================
TEST_F(ParserTest, TestRectAsm)
{
    std::filesystem::path filepath = base_path / "06/Rect.asm";
    Parser parser(filepath.string());

    // @R0
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::A_Command);
    EXPECT_EQ(parser.symbol(), "R0");

    // D=M
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "M");

    // @END
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "END");

    // D;JLE
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::C_Command);
    EXPECT_EQ(parser.dest(), "");
    EXPECT_EQ(parser.comp(), "D");
    EXPECT_EQ(parser.jump(), "JLE");

    // @n
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "n");

    // M=D
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "M");
    EXPECT_EQ(parser.comp(), "D");

    // @SCREEN
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "SCREEN");

    // D=A
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "A");

    // @addr
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "addr");

    // M=D
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "M");
    EXPECT_EQ(parser.comp(), "D");

    // (LOOP)
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::L_Command);
    EXPECT_EQ(parser.symbol(), "LOOP");

    // @addr
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "addr");

    // A=M
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "A");
    EXPECT_EQ(parser.comp(), "M");

    // M=-1
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "M");
    EXPECT_EQ(parser.comp(), "-1");

    // @addr
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "addr");

    // D=M
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "M");

    // @32
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "32");

    // D=D+A
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "D+A");

    // @addr
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "addr");

    // M=D
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.dest(), "M");
    EXPECT_EQ(parser.comp(), "D");

    // @n
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "n");

    // MD=M-1  <-- Crucial test for multi-register destination parsing!
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::C_Command);
    EXPECT_EQ(parser.dest(), "MD");
    EXPECT_EQ(parser.comp(), "M-1");
    EXPECT_EQ(parser.jump(), "");

    // @LOOP
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "LOOP");

    // D;JGT
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.jump(), "JGT");

    // (END)
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.commandType(), Parser::CommandType::L_Command);
    EXPECT_EQ(parser.symbol(), "END");

    // @END
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.symbol(), "END");

    // 0;JMP
    ASSERT_TRUE(parser.advance());
    EXPECT_EQ(parser.jump(), "JMP");

    EXPECT_FALSE(parser.advance());
}
