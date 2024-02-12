#pragma once

#include <cassert>
#include <cstdint>
#include <elf.h>
#include <string>
#include <vector>

namespace mem {

using address_t = uint32_t;

struct segment
{
    address_t _initial_address;
    std::vector<uint8_t> _content;

    segment() : _initial_address(0), _content() {}
    segment(address_t initial_address, size_t size) : _initial_address(initial_address), _content(size) {}
};

class memory
{
  private:
    std::vector<uint8_t> _binary;
    Elf32_Ehdr _ehdr; // ELF header
    std::vector<Elf32_Phdr> _phdr; // Program header table, may contain multiple entries
    std::vector<segment> _segments;

  public:

    constexpr static size_t stack_top = 128 * 1024 * 1024; // the stack segment is always the first
    constexpr static size_t stack_size = 1024 * 1024; // the stack segment is always the first

    memory() : _binary(), _ehdr(), _phdr(), _segments() {
        // initialize the stack
        _segments.push_back(segment(stack_top-stack_size, stack_size)); // initial 1MB stack
    }

    ssize_t find_segment(address_t addr) const {
        size_t i = 0;
        for(; i < _segments.size(); ++i){
            auto begin = _segments[i]._initial_address;
            auto end = begin + _segments[i]._content.size();
            if((begin <= addr) && (addr < end)) {
                return static_cast<ssize_t>(i);
            }
        }
        return -1;
    }

  template<typename T>
  T read(address_t addr)
  {
    // find the segment
    auto seg_idx = find_segment(addr);
    assert(seg_idx != -1);

    // read the data
    auto pos = addr - _segments[seg_idx]._initial_address;
    // ensure alignment
    assert ((pos & (sizeof(T) - 1)) == 0);

    return *reinterpret_cast<T*>(&_segments[seg_idx]._content[pos]);
  }

  template<typename T>
  void write(address_t addr, T value)
    {
      // find the segment
      auto seg_idx = find_segment(addr);
      assert(seg_idx != -1);

      // read the data
      auto pos = addr - _segments[seg_idx]._initial_address;
      // ensure alignment
      assert ((pos & (sizeof(T) - 1)) == 0);

      for(size_t i = 0; i < sizeof(T); ++i) {
        _segments[seg_idx]._content[pos+i]=value & 0xFF;
        value = value >> 8;
      }
    }

        void load_binary(const std::string& binfile);

  address_t entry_point() const { return _ehdr.e_entry; }
};

} // namespace mem
