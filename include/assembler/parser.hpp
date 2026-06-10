#ifndef PARSER_HPP
#define PARSER_HPP

#include <stdio.h>
#include <fstream>

using namespace std;


class Parser
{
private:
	std::fstream p;
	std::string currentCommand;
public:
	Parser(std::string asm_file);
	bool hasMoreCommands();
	void advance();
	enum class CommandType(A_Command, C_Command, L_Command);
	CommandType commandType();
	const std::string symbol(){

	};
	const std::string dest();
	const std::string comp();
	const std::string jump();


};

#endif
