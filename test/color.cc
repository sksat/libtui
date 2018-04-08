#include "../tui.hpp"

using namespace tui::color;

void print(color4_t col, const char* str, bool blight=false){
	if(blight)
		col = col.get_blight();
	col.set();
	printf(str);
}

void print_colname(bool b){
	print(Red, "Red ", b);
	print(Green, "Green ", b);
	print(Yellow, "Yellow ", b);
	print(Blue, "Blue ", b);
	print(Magenta, "Magenta ", b);
	print(Cyan, "Cyan ", b);
	print(White, "White\n", b);
}

void test_4bitcol(){
	color4_t col = Black;
	while(true){
		col.set_back();
		print_colname(true);
		print_colname(false);
		col.get_blight().set_back();
		print_colname(true);
		print_colname(false);
		if(!col.has_next()) break;
		col = col.get_next();
	}
}

int main(int argc, char **argv){
	using namespace tui;
	try{
		test_4bitcol();
	}catch(const char* msg){
		printf(msg);
	}
}
