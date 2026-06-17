#include "assembler/symbolTable.hpp"
#include <optional>

SymbolTable::SymbolTable() { symbolTable = {}; };

void SymbolTable::addEntry(const std::string &symbol, uint16_t address)
{
    symbolTable.insert({symbol, address});
}
bool SymbolTable::contains(const std::string &symbol) const
{
    if (symbolTable.find(symbol) != symbolTable.end())
    {
        return true;
    }
    else
        return false;
}
std::optional<std::uint16_t>
SymbolTable::getAddress(const std::string &symbol) const
{
    auto it = symbolTable.find(symbol);
    if (it != symbolTable.end())
    {
        return it->second;
    }
    return std::nullopt;
}
