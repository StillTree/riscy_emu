#pragma once

#include "typedefs.hpp"

#include <span>
#include <vector>

namespace riscy_emu {

class mmio_dev {
public:
	virtual ~mmio_dev() = default;
	virtual auto read(usz offset, usz size) -> u64 = 0;
	virtual auto write(usz offset, usz size, u64 val) -> void = 0;
};

struct bus_mapping {
	mmio_dev* mmio_dev = nullptr;
	std::span<std::byte, 4096> mem { };
	u64 mapping_offset = 0;

	[[nodiscard]] auto is_ram() const -> bool
	{
		return !mem.empty();
	}
};

class mem_bus {

private:
	std::vector<bus_mapping> pages;
};

}
