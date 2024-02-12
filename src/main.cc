#include <iostream>
#include <map>

#include <instructions.hh>
#include <memory.hh>
#include <processor.hh>

using namespace instrs;
using namespace mem;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Invalid Syntax: peRISCVcope <program>" << std::endl;
        exit(1);
    }

   memory mem;
   processor proc;

   mem.load_binary(argv[1]);

   // read the entry point
   // ...

   proc.write_pc(mem.entry_point());

   // set the stack pointer
   // the stack grows downward with the stack pointer always being 16-byte aligned
   proc.write_reg(processor::sp, memory::stack_top);

   address_t pc = 0xDEADBEEF, next_pc = 0xDEADBEEF;

   size_t exec_instrs = 0;
   do
   {
       // main interpreter loop
       // ...
       exec_instrs++;
   } while (next_pc != pc); // look for while(1) in the code

   std::cout << "Number of executed instructions: " << exec_instrs << std::endl;
}
