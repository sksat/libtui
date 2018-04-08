#ifndef TUI_COLOR_HPP_
#define TUI_COLOR_HPP_

#include "screen.hpp"

namespace tui {
	namespace color {
		struct color4_t {
			constexpr color4_t() : num(7) {}
			constexpr color4_t(const char num) : num(num) {
				if(num == 8 || num == 9 || num > 18)
					throw "error: color4_t num"; // コンパイル時にエラーになる
			}
		private:
			char num;
		public:
			constexpr char get_num() const { return num; }
			constexpr bool has_next() const { return (num==17 ? false : true); }
			constexpr color4_t get_next() const { return color4_t(get_num()==7 ? 10 : get_num()+1); }
			constexpr color4_t get_blight() const { return color4_t(get_num()>7 ? get_num() : get_num()+10); }
			void set() const {
				std::string com = "[";
				if(num < 8)
					com += "3" + std::to_string(static_cast<int>(num));
				else
					com += "9" + std::to_string(static_cast<int>(num-10));
				com += "m";
				screen::esc(com);
			}
			void set_back() const {
				if(num < 8)
					printf("\e[4%dm", static_cast<int>(num));
				else
					printf("\e[10%dm", static_cast<int>(num-10));
			}
		};

		constexpr auto Black	= color4_t(0);
		constexpr auto Red	= color4_t(1);
		constexpr auto Green	= color4_t(2);
		constexpr auto Yellow	= color4_t(3);
		constexpr auto Blue	= color4_t(4);
		constexpr auto Magenta	= color4_t(5);
		constexpr auto Cyan	= color4_t(6);
		constexpr auto White	= color4_t(7);
		constexpr color4_t Blight(color4_t c){ return c.get_blight(); }
		constexpr auto BrightBlack	= Blight(Black);
		constexpr auto BlightRed	= Blight(Red);
		constexpr auto BlightGreen	= Blight(Green);
		constexpr auto BlightYellow	= Blight(Yellow);
		constexpr auto BlightBlue	= Blight(Blue);
		constexpr auto BlightMagenta	= Blight(Magenta);
		constexpr auto BlightCyan	= Blight(Cyan);
		constexpr auto BlightWhite	= Blight(White);
	}
}

#endif
