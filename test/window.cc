#include "../tui.hpp"
#include <iostream>

int main(int argc, char **argv){
	using namespace tui;

	config::raw().set();
	screen::push_title();
	screen::enter_ca_mode();

	window win;
	std::cout<<"window: width="<<win.get_width()<<", height="<<win.get_height()<<std::endl;

//	win.set_colback(color::Blue);

	while(true){
		auto key = keyboard::get();
		switch(key){
		case 'q': goto fin;
		case keyboard::Enter:
			win.draw();
			printf("\n~\n\10~\n\10~\n\10~\n");
			printf("\10aaa");
			screen::flush();
			break;
		default:
			break;
		}
	}
fin:
	color::Black.set_back();
	screen::clear();

	screen::exit_ca_mode();
	screen::pop_title();
}
