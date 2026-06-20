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
    bool isNumber(const std::string &s)
    {
        return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
    }
    void assembleFile(const std::string &inputRelativePath,
                      const std::string &outputRelativePath)
    {
        std::filesystem::path filepath = basepath / inputRelativePath;
        std::filesystem::path outPath = basepath / outputRelativePath;

        // Ensure the output directory exists
        std::filesystem::create_directories(outPath.parent_path());

        SymbolTable table = SymbolTable();
        Parser p(filepath.string());
        std::ofstream output(outPath);

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
        int variable = 16;
        while (p2.advance())
        {
            if (p2.commandType() == Parser::CommandType::A_Command)
            {
                if (isNumber(p2.symbol()))
                {
                    output << "@" << p2.symbol() << std::endl;
                }
                else if (table.contains(p2.symbol()))
                {
                    output << "@" << table.getAddress(p2.symbol()) << std::endl;
                }
                else
                {
                    table.addEntry(p2.symbol(), variable);
                    output << "@" << variable << std::endl;
                    ++variable;
                }
                continue;
            }

            if (p2.commandType() == Parser::CommandType::L_Command)
            {
                continue;
            }

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
};

TEST_F(Symbol_test, TestMaxSymbols)
{
    assembleFile("06/Max.asm", "output/MaxStest.asm");
}

TEST_F(Symbol_test, VerifyRectOutputs)
{

    assembleFile("06/Rect.asm", "output/RectSymboltest.asm");
    // 1. Define paths to both files
    std::filesystem::path originalPath = basepath / "06/RectL.asm";
    std::filesystem::path parsedPath = basepath / "output/RectSymboltest.asm";

    // 2. Initialize both parsers
    Parser p1(originalPath.string());
    Parser p2(parsedPath.string());

    // 3. Step through both files simultaneously
    while (true)
    {
        bool hasNext1 = p1.advance();
        bool hasNext2 = p2.advance();

        // Assert that BOTH files finish at the exact same time.
        // If one file has fewer instructions than the other, this fails
        // immediately.
        ASSERT_EQ(hasNext1, hasNext2)
            << "The files have a mismatched number of instructions!";

        // If we reached the end of both files successfully, break the loop
        if (!hasNext1 && !hasNext2)
        {
            break;
        }

        // 4. Run cross-assertions on the commands
        // The command types must match exactly (except L_Commands which should
        // be stripped)
        ASSERT_EQ(p1.commandType(), p2.commandType())
            << "Command type mismatch at line count!";

        if (p1.commandType() == Parser::CommandType::A_Command)
        {
            // For RectL vs RectSymboltest, check that the address matches.
            // If RectSymboltest correctly resolved a symbol like @counter to
            // @16, and RectL already had @16, they should now match perfectly.
            EXPECT_EQ(p1.symbol(), p2.symbol())
                << "A-instruction address mismatch! Original: @" << p1.symbol()
                << " | Parsed: @" << p2.symbol();
        }
        else if (p1.commandType() == Parser::CommandType::C_Command)
        {
            // Verify all components of the C-instruction are identical
            EXPECT_EQ(p1.dest(), p2.dest()) << "C-Instruction Dest mismatch!";
            EXPECT_EQ(p1.comp(), p2.comp()) << "C-Instruction Comp mismatch!";
            EXPECT_EQ(p1.jump(), p2.jump()) << "C-Instruction Jump mismatch!";
        }
    }
}

TEST_F(Symbol_test, VerifyPongOutputs)
{

    assembleFile("06/PongL.asm", "output/PongStest.asm");
    // 1. Define paths to both files
    std::filesystem::path originalPath = basepath / "06/PongL.asm";
    std::filesystem::path parsedPath = basepath / "output/PongStest.asm";

    // 2. Initialize both parsers
    Parser p1(originalPath.string());
    Parser p2(parsedPath.string());

    // 3. Step through both files simultaneously
    while (true)
    {
        bool hasNext1 = p1.advance();
        bool hasNext2 = p2.advance();

        // Assert that BOTH files finish at the exact same time.
        // If one file has fewer instructions than the other, this fails
        // immediately.
        ASSERT_EQ(hasNext1, hasNext2)
            << "The files have a mismatched number of instructions!";

        // If we reached the end of both files successfully, break the loop
        if (!hasNext1 && !hasNext2)
        {
            break;
        }

        // 4. Run cross-assertions on the commands
        // The command types must match exactly (except L_Commands which should
        // be stripped)
        ASSERT_EQ(p1.commandType(), p2.commandType())
            << "Command type mismatch at line count!";

        if (p1.commandType() == Parser::CommandType::A_Command)
        {
            // For RectL vs RectSymboltest, check that the address matches.
            // If RectSymboltest correctly resolved a symbol like @counter to
            // @16, and RectL already had @16, they should now match perfectly.
            EXPECT_EQ(p1.symbol(), p2.symbol())
                << "A-instruction address mismatch! Original: @" << p1.symbol()
                << " | Parsed: @" << p2.symbol();
        }
        else if (p1.commandType() == Parser::CommandType::C_Command)
        {
            // Verify all components of the C-instruction are identical
            EXPECT_EQ(p1.dest(), p2.dest()) << "C-Instruction Dest mismatch!";
            EXPECT_EQ(p1.comp(), p2.comp()) << "C-Instruction Comp mismatch!";
            EXPECT_EQ(p1.jump(), p2.jump()) << "C-Instruction Jump mismatch!";
        }
    }
}
