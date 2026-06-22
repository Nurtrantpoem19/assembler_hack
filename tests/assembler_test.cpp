#include "assembler/Assembler.hpp"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

namespace fs = std::filesystem;

std::vector<std::string> readFile(const fs::path &path)
{
    std::vector<std::string> lines;
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    return lines;
}

TEST(AssemblerTest, MatchesGoldenOutput)
{
    fs::path hackFile = "06/Pong.hack";
    fs::path goldenFile = "golden/Pong.golden";

    // 2. Read contents
    auto actual = readFile(hackFile);
    auto expected = readFile(goldenFile);

    // 3. Compare sizes
    ASSERT_EQ(actual.size(), expected.size()) << "File lengths differ!";

    // 4. Compare line by line
    for (size_t i = 0; i < expected.size(); ++i)
    {
        EXPECT_EQ(actual[i], expected[i]) << "Mismatch at line " << i + 1;
    }
}
