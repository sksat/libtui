#include "../tui.hpp"

void print(tui::color::color4_t col, const char* str, bool blight=false){
	if(blight)
		col = col.get_blight();
	col.set();
	printf(str);
}

void test_4bitcol(bool b){
	using namespace tui::color;
	print(Red, "Red ", b);
	print(Green, "Green ", b);
	print(Yellow, "Yellow ", b);
	print(Blue, "Blue ", b);
	print(Magenta, "Magenta ", b);
	print(Cyan, "Cyan ", b);
	print(White, "White\n", b);
}

int main(int argc, char **argv){
	using namespace tui;

	test_4bitcol(false);
	test_4bitcol(true);
}
