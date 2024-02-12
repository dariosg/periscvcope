#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>

#include <memory.hh>

using namespace mem;

void
memory::load_binary(const std::string& binfile)
{
    using ifile_iter = std::istream_iterator<uint8_t>;

    std::ifstream ifile(binfile, std::ios::binary);

    if (ifile.is_open() == false) {
	std::cerr << "Unable to open "<< binfile << std::endl;
	std::exit(EXIT_FAILURE);
    }

    // copy the binary into memory
    // Stop eating new lines in binary mode!!!
    ifile.unsetf(std::ios::skipws);

    ifile.seekg(0, std::ios::end);
    const auto ifsize = ifile.tellg();
    ifile.seekg(0, std::ios::beg);

    _binary.reserve(ifsize);
    _binary.insert(_binary.begin(),
	    ifile_iter(ifile),
	    ifile_iter());
    ifile.close();


    // read elf header

    // ensure riscv32

    // ensure the binary has a correct program table


    // entry point
    // load sections in memory
    // read ELF program header table,
    // ... to be completed
}
