#include "config.hpp"
#include <unistd.h>
#include <termios.h>

using namespace tui;

config config::now(){
	config c;
	termios t;
	tcgetattr(STDIN_FILENO, &t);

	auto& l = t.c_lflag;
	if(l & ECHO)	c.echo = true;
	if(l & ECHOE)	c.erace= true;
	if(l & ICANON)	c.canonical = true;
	if(l & ISIG)	c.signal = true;
	return c;
}

termios old_term;

void config::set(const config &c){
	termios t;
	tcgetattr(STDIN_FILENO, &t);
	old_term = t;

	auto& l = t.c_lflag;
	l &= c.echo << ECHO;
	l &= c.erace << ECHOE;
	l &= c.canonical << ICANON;
	l &= c.signal << ISIG;

	if(c == raw) cfmakeraw(&t); // 手抜き

	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	return;
}

void config::fix(){
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
}
