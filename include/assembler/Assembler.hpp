#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include "assembler/Parser.hpp"

#include "assembler/symbolTable.hpp"
#include <filesystem>
#include <fstream>

class Assembler
{
  protected:
    SymbolTable table;
    Parser parser;
    Parser parser2;
    std::ofstream output_obj;
    static bool isNumber(const std::string &s);

  public:
    Assembler(std::filesystem::path &input, std::filesystem::path &output);
    void assemble();
};
#endif
