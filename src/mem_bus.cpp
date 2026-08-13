#include "mem_bus.hpp"

namespace riscy_emu {

mem_bus::mem_bus(usz max_mem)
{
	pages.resize(max_mem >> PAGE_SHIFT);
}

template <numeric T> auto mem_bus::read(addr addr) const -> T { }

template <numeric T> auto mem_bus::write(addr addr, T val) -> void { }

}
