#include "assembler/Assembler.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "need input path" << std::endl;
    }

    std::filesystem::path filepath = argv[1];
    std::filesystem::path outpath = filepath;
    outpath.replace_extension(".hack");

    Assembler main(filepath, outpath);
    main.assemble();
}
