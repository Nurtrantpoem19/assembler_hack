#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>

class SymbolTable
{
  private:
    std::unordered_map<std::string, uint16_t> symbolTable;

  public:
    SymbolTable();
    void addEntry(const std::string &symbol, uint16_t address);
    bool contains(const std::string &symbol) const;
    std::optional<std::uint16_t> getAddress(const std::string &symbol) const;
};
#endif // SYMBOLTABLE_HPP
