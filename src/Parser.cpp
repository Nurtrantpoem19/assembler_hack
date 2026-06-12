#include "Parser.hpp"
#include <fstream>

Parser::Parser(std::string asm_file) : p(asm_file)

{
    std::getline(p, currentCommand);
    p
}

bool Parser::hasMoreCommands() { return p.peek() != EOF; }

void Parser::advance()
{
    while (std::getline(p, currentCommand))
    {

	std::size_t start = currentCommand.find("//");
	if (start != std::string::npos)
	{
	    currentCommand = currentCommand.substr(0, start);
	}
	auto start = std::find_if_not(s.begin(), s.end(), [](unsigned char ch)
				      { return std::isspace(ch); })

	    // 2. Find the last non-space character (searching backward)
	    auto end =
		std::find_if_not(s.rbegin(), s.rend(), [](unsigned char ch)
				 { return std::isspace(ch); })
		    .base();

	s.erase(end, s.end());

	s.erase(s.begin(), start);
    }
};

Parser::CommandType Parser::commandType() const
{
    if (currentCommand.empty())
    {
	return CommandType::Not_Command;
    }

    switch (currentCommand[0])
    {
    case (' '):
    case ('	'):
	return CommandType::Not_Command;
    case '/':
	if (currentCommand[1] == '/')
	    return CommandType::Not_Command;
	break;
    case ('@'):
	return CommandType::A_Command;
    case ('('):
	return CommandType::L_Command;
    default:
	return CommandType::C_Command;
    }
}
