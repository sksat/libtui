#include "../tui.hpp"

int main(int argc, char **argv){
	using namespace tui;

	config::raw().set();
	screen::push_title();
	screen::enter_ca_mode();

	window win;
//	win.set_colback(color::Red);

	while(true){
		auto key = keyboard::get();
		switch(key){
		case 'q': exit(0); break;
		case keyboard::Enter:
			win.draw();
			printf("aaaaaaaaa");
			screen::flush();
			break;
		default:
			break;
		}
	}
	color::Black.set_back();
	screen::clear();

	screen::exit_ca_mode();
	screen::pop_title();
}
