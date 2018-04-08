#ifndef TUI_SCREEN_HPP_
#define TUI_SCREEN_HPP_

#include <cstddef>
#include <string>

namespace tui {
	namespace screen {
		struct info {
			size_t width, height;
		};

		const info get_info();

		void set_color();

		void esc(const std::string&); // エスケープシーケンス
		void csi(const std::string&); // CSIシーケンス

		void clear();
		void flush();

		void push_title();
		void pop_title();

		void enter_ca_mode();
		void exit_ca_mode();
	}
}

#endif
