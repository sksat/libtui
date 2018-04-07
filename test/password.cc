#include "../tui.hpp"
#include <stdio.h>
#include <string>
#include <iostream>

int main(int argc, char **argv){
	using namespace tui;
	config::password().set();

	std::string pass;

	std::cout<<"pasword: ";
	std::cin>>pass;

	config::fix();

	std::cout<<std::endl<<"pass: "<<pass<<std::endl;
}
