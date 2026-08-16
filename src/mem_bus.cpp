#include "mem_bus.hpp"

#include <cstring>

namespace riscy_emu {

mem_bus::mem_bus(addr max_mem)
{
	pages.resize(max_mem >> PAGE_SHIFT);
}

template <numeric T> auto mem_bus::read(addr address) const -> std::expected<T, mem_bus_err>
{
	if (!is_aligned<T>(address)) {
		return std::unexpected(mem_bus_err::other);
	}

	const usz page_index = address >> PAGE_SHIFT;
	if (page_index >= pages.size()) {
		return std::unexpected(mem_bus_err::other);
	}

	const auto& page = pages[page_index];
	const addr offset = address & PAGE_OFFSET_MASK;

	if (page.is_ram()) {
		T val;
		std::memcpy(&val, page.mem.data() + offset, sizeof val);
		return val;
	}

	return static_cast<T>(page.dev->read(offset, sizeof(T)));
}

template <numeric T> auto mem_bus::write(addr address, T val) -> std::expected<void, mem_bus_err>
{
	if (!is_aligned<T>(address)) {
		return std::unexpected(mem_bus_err::other);
	}

	const usz page_index = address >> PAGE_SHIFT;
	if (page_index >= pages.size()) {
		return std::unexpected(mem_bus_err::other);
	}

	const auto& page = pages[page_index];
	const addr offset = address & PAGE_OFFSET_MASK;

	if (page.is_ram()) {
		std::memcpy(page.mem.data() + offset, &val, sizeof val);
		return { };
	}

	return static_cast<T>(page.dev->write(offset, sizeof val, val));
}

}
