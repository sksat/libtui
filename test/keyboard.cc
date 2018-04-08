#include "../tui.hpp"

int main(int argc, char **argv){
	using namespace tui::keyboard;
	tui::config::raw().set();
	while(true){
		auto k = get();
		switch(k){
		case 'q': exit(0);
		case Enter: printf("\n"); break;
		default:
			if(k.is_print)
				printf("%c\n", k.c);
			else
				printf("%s\n", key2str(k).c_str());
			break;
		}
	}
}
