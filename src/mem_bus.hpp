#pragma once

#include "typedefs.hpp"

#include <concepts>
#include <span>
#include <type_traits>
#include <vector>

namespace riscy_emu {

class mmio_dev {
public:
	virtual ~mmio_dev() = default;
	virtual auto read(usz offset, usz size) -> u64 = 0;
	virtual auto write(usz offset, usz size, u64 val) -> void = 0;
};

struct bus_mapping {
	mmio_dev* dev = nullptr;
	std::span<std::byte> mem;
	addr mapping_offset = 0;

	[[nodiscard]] auto is_ram() const -> bool
	{
		return !mem.empty();
	}
};

template <typename T>
concept numeric = std::integral<T> && !std::is_same_v<T, bool>;

class mem_bus {
public:
	explicit mem_bus(addr max_mem = 0x100000000);

	template <numeric T> [[nodiscard]] auto read(addr addr) const -> T;
	template <numeric T> auto write(addr addr, T val) -> void;

private:
	static constexpr addr PAGE_SHIFT = 12;
	static constexpr addr PAGE_OFFSET_MASK = 0xfff;

	std::vector<bus_mapping> pages;
};

}
