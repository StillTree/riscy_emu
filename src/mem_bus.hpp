#pragma once

#include "typedefs.hpp"

#include <concepts>
#include <expected>
#include <span>
#include <vector>

namespace riscy_emu {

enum class mem_bus_err : u8 {
	other,
};

// TODO: I don't like always returning a u64, to think about...
class mmio_dev {
public:
	virtual ~mmio_dev() = default;
	virtual auto read(usz offset, usz size) -> std::expected<u64, mem_bus_err> = 0;
	virtual auto write(usz offset, usz size, u64 val) -> std::expected<void, mem_bus_err> = 0;
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
concept numeric = std::integral<T> && !std::same_as<T, bool>;

template <numeric T> [[nodiscard]] constexpr auto is_aligned(addr address) noexcept -> bool
{
	return (address % sizeof(T)) == 0;
}

class mem_bus {
public:
	explicit mem_bus(addr max_mem = 0x100000000);

	template <numeric T> [[nodiscard]] auto read(addr address) const -> std::expected<T, mem_bus_err>;
	template <numeric T> auto write(addr address, T val) -> std::expected<void, mem_bus_err>;

private:
	static constexpr addr PAGE_SHIFT = 12;
	static constexpr addr PAGE_OFFSET_MASK = 0xfff;

	std::vector<bus_mapping> pages;
};

}
