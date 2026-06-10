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
    void addEntry(const std::string &symbol, int address);
    bool contains(const std::string &symbol);
    std::optional<std::uint16_t> getAddress(const std::string &symbol) const;
};
#endif // SYMBOLTABLE_HPP
