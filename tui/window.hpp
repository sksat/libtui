#ifndef TUI_WINDOW_HPP_
#define TUI_WINDOW_HPP_

#include "screen.hpp"
#include "color.hpp"

namespace tui {
	class window {
	public:
		window() : col_bk(color::Black) {
			// とりあえずスクリーンと同じサイズ
			auto i = screen::get_info();
			width = i.width;
			height= i.height;
		}
		window(size_t w, size_t h) : width(w), height(h), col_bk(color::Black) {}
		window(size_t w, size_t h, color::color4_t c) : width(w), height(h), col_bk(c) {}

		size_t get_width() const { return width; }
		size_t get_height()const { return height;}

		void set_width(size_t w){ width = w; }
		void set_height(size_t h){height= h; }
		void set_colback(const color::color4_t &c){ col_bk = c; }

		void draw(){
			col_bk.set_back();
			screen::clear();
		}
	private:
		size_t width, height;
		color::color4_t col_bk;
	};
}

#endif
