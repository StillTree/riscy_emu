#include "machine.hpp"

namespace riscy_emu {

auto machine::run() -> void
{
	while (true) {
		hart.step();
	}
}

}
