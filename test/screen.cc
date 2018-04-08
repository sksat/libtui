#include "../tui.hpp"

int main(int argc, char **argv){
	using namespace tui;
	config::raw().set();
	printf("\n");
	while(true){
		screen::clear();
		auto key = keyboard::get();
		switch(key){
		case 'q': exit(0);
		default:
			printf("%s\n", key2str(key).c_str());
			break;
		}
	}
}
