#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <stdio.h>

using namespace std;

class Parser
{
  private:
    std::ifstream p;
    std::string currentCommand;

  public:
    Parser(const std::string asm_file);
    bool hasMoreCommands();
    void advance();
    enum class CommandType
    {
	A_Command,
	C_Command,
	L_Command,
	Not_Command
    };
    CommandType commandType() const;
    std::string symbol() const;
    std::string dest() const;
    std::string comp() const;
    std::string jump() const;
};

#endif
