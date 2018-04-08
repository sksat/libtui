#ifndef TUI_KEYBOARD_HPP_
#define TUI_KEYBOARD_HPP_

#include <string>

namespace tui {
	namespace keyboard {
		struct key {
			constexpr key() :
				is_print(false), alt(false), ctrl(false), shift(false), fn(false), extend(false), c(0x00) {}
			constexpr key(bool is, bool a, bool ct, bool s, bool f, bool e, char c) :
				is_print(is), alt(a), ctrl(ct), shift(s), fn(f), extend(e), c(c) {}

			static constexpr key ext(char n){
				return key(false, false, false, false, false, true, n);
			}

			static constexpr key f(char n){
				return key(false, false, false, false, true, false, n);
			}

			constexpr operator int() const {
				return (!is_print << 14 |
					alt << 13 |
					ctrl << 12 |
					shift << 11 |
					fn << 10 |
					extend << 9 |
					c);
			}

			bool is_print;
			bool alt, ctrl, shift;
			bool fn;
			bool extend;
			char c;

			struct extnum{
				enum : char {
					Up = 0x01,
					Down,
					Right,
					Left,
					Insert,
					Delete,
					PgUp,
					PgDown,
					End,
					Home,
				};
			};
		};

		//			    //is_p,  alt,   ctrl,  shift, fn,    ext,   c
		constexpr key Tab	= key(true,  false, false, false, false, false, 0x09);
		constexpr key Enter	= key(false, false, false, false, false, false, 0x0d);
		constexpr key BackSpace	= key(false, false, false, false, false, false, 0x7f);
		constexpr key Esc	= key(false, false, false, false, false, false, 0x1b);
		constexpr key Up	= key::ext(key::extnum::Up);
		constexpr key Down	= key::ext(key::extnum::Down);
		constexpr key Right	= key::ext(key::extnum::Right);
		constexpr key Left	= key::ext(key::extnum::Left);
		constexpr key Insert	= key::ext(key::extnum::Insert);
		constexpr key Delete	= key::ext(key::extnum::Delete);
		constexpr key PgUp	= key::ext(key::extnum::PgUp);
		constexpr key PgDown	= key::ext(key::extnum::PgDown);
		constexpr key End	= key::ext(key::extnum::End);
		constexpr key Home	= key::ext(key::extnum::Home);

		const std::string key2str(const key&);

		const key get();
	}
}

#endif
