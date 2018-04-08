#ifndef TUI_COLOR_HPP_
#define TUI_COLOR_HPP_

namespace tui {
	namespace color {
		struct color4_t {
			constexpr color4_t(const char num) : num(num) {
				if(num == 8 || num == 9 || num > 18)
					throw "error: color4_t num"; // コンパイル時にエラーになる
			}

			char num;

			void set() const {
				if(num < 8)
					printf("\e[3%dm", static_cast<int>(num));
				else
					printf("\e[9%dm", static_cast<int>(num-10));
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
		constexpr color4_t Blight(color4_t c){
			if(c.num > 7) throw "error";
			c.num+=10;
			return c;
		}
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
