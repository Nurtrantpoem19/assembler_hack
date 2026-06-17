#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include "HashTable.hpp"
#include <cstdint>
#include <optional>
#include <string>

class SymbolTable
{
  private:
    HashTable table;

  public:
    SymbolTable();
    void addEntry(const std::string &symbol, std::uint16_t address);
    bool contains(const std::string &symbol) const;
    std::optional<std::uint16_t> getAddress(const std::string &symbol) const;
};
#endif // SYMBOLTABLE_HPP
