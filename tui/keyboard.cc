#include "keyboard.hpp"
#include <unistd.h>

namespace tui { namespace keyboard {

const key get(){
	key k;
	k.is_print = k.alt = k.ctrl = k.shift = false;

	char buf[7];
	buf[1] = buf[2] = 0x00;
	read(STDIN_FILENO, buf, 7);

//	for(int i=0;i<7;i++) printf("%x ", static_cast<unsigned char>(buf[i]));

	const char& c0 = buf[0];

	// 1 byte
	if(c0 != 0x1b){
		k.c = c0;
		if(0x01 <= c0 && c0 <= 0x1a){ // 0x01-0x1a
			switch(c0){
			case 0x09: k.is_print = true; break; // Tab
			case 0x0d: break; // Enter
			default:
				k.ctrl = true;
				k.c += 0x60;
				break;
			}
		}else if(0x20 <= c0 && c0 <= 0x7f){ // 0x20-0x7f
			k.is_print = (c0!=0x7f ? true : false); // BackSpace以外は普通の文字
		}else{
			k.c = 0x00; // unknown
		}
		return k;
	}

	// multi byte
	const char& c1 = buf[1];
	const char& c2 = buf[2];
	const char& c3 = buf[3];
	const char& c4 = buf[4];
	const char& c5 = buf[5];
	const char& c6 = buf[6];
	if(c1 == 0x00){
		// Esc
		k.c = c0;
	}else if(0x27 <= c1 && c1 <= 0x5a){ // 0x27-0x5a
		k.c = c1;
		if(	(0x27<=c1 && c1<=0x2b)			// Alt+Shift+(`'`-`+`)
			|| (0x41<=c1 && c1<=0x4f && c2==0x00)	// Alt+Shift+(a-o)
			|| (0x50<=c1 && c1<=0x5a)){		// Alt+Shift+(p-z)

			k.alt = k.shift = true;
		}else if(c1 == 0x4f && (0x50 <= c2 && c2 <= 0x53)){ // F1-F4
			k.fn = true;
			k.c  = c2 - 0x50 + 1;
		}else{
			k.c = 0x00; // unknown
		}
	}else if(c1 == 0x5b){
		if(c2 == 0x31){
			if(0x35 <= c3 && c3 <= 0x39){ // F(5-8)
				k.fn = true;
				k.c = c3 - 0x30;
				if(c3 != 0x35) k.c--;
				if(c4 != 0x7e){
					if(c4 == 0x3b && c5 == 0x32 && c6 == 0x7e){
						// +Shift
						k.shift = true;
					}else{
						k.c = 0x00; // unknown
					}
				}
			}else if(c3==0x3b && c4==0x32){ // Shift
				k.shift = true;
				switch(c5){
				case 0x41: // +Up
				case 0x42: // +Down
				case 0x43: // +Right
				case 0x44: // +Left
					k.extend = true;
					k.c = key::extnum::Up + (c5-0x41);
					break;
				case 0x50:
				case 0x51:
				case 0x52:
				case 0x53:
					// +F(1-4)
					k.fn = true;
					k.c = c5 - 0x50 + 1;
					break;
				default:
					k.c = 0x00; // unknown
					break;
				}
			}else{
				k.c = 0x00; //unkwnon
			}
		}else if(c2 == 0x32){
			switch(c3){
			case 0x30:
			case 0x31:
			case 0x34:
				// F(9,10,12)
				k.fn = true;
				k.c = c3 - 0x27;
				if(c3 == 0x34) k.c--;
				if(c4==0x3b && c5==0x32 && c6==0x7e)
					k.shift = true;
				else if(c4!=0x7e) k.c = 0x00;
				break;
			case 0x7e: // Insert
				k.extend = true;
				k.c = key::extnum::Insert;
				break;
			default:
				k.c = 0x00; // unknwon
			}
		}else if(c2 == 0x33){
			k.extend = true;
			if(c3==0x3b && c4==0x32 && c5==0x7e){
				// Shift+Delete
				k.shift = true;
				k.c = key::extnum::Delete;
			}else if(c3==0x7e){
				// Delete
				k.c = key::extnum::Delete;
			}
		}else if((c2==0x35 || c2==0x36) && c3==0x7e){
			k.extend = true;
			if(c2 == 0x35) k.c = key::extnum::PgUp; // PgUp
			else k.c = key::extnum::PgDown; // PgDown
		}else if(0x41<=c2 && c2<=0x48){
			k.extend = true;
			switch(c2){
			case 0x41: // Up
			case 0x42: // Down
			case 0x43: // Right
			case 0x44: // Left
				k.c = key::extnum::Up + (c2-0x41);
				break;
			case 0x46: k.c = key::extnum::End; break; // End
			case 0x48: k.c = key::extnum::Home; break; // Home
			default:
				k.c = 0x00; // unknwon
				break;
			}
		}else{
			k.c = 0x00; // unknwon
		}
	}else if(0x5c <= c1 && c1 <= 0x7c){ // 0x5c-0x7c
		// Alt+(a-z)
		k.alt = true;
		k.c = c1;
	}else{
		k.c = 0x00; // unknwon
	}

	return k;
}


const std::string key2str(const key &k){
	std::string str;
	if(k.is_print){
		if(k == Tab) return "Tab";
		else return (str+=k.c);
	}
	if(k.ctrl) str+="Ctrl+";
	if(k.alt) str+="Alt+";
	if(k.shift){
		if(k.is_print && 'A'<=k.c && k.c<='Z'){}
		else str+="Shift+";
	}
	if(k.fn){
		str+= "F" + std::to_string(static_cast<int>(k.c));
		return str;
	}

	if(k.c == 0x00) str+="unknown";
	else if(k.extend){
		switch(k.c){
		#define EXT_KEY(k) case (key::extnum::k): str+= (#k); break;
		EXT_KEY(Up);
		EXT_KEY(Down);
		EXT_KEY(Right);
		EXT_KEY(Left);
		EXT_KEY(Insert);
		EXT_KEY(Delete);
		EXT_KEY(PgUp);
		EXT_KEY(PgDown);
		EXT_KEY(End);
		EXT_KEY(Home);
		}
	}else{
		if(k == Enter) str+="Enter";
		else if(k == BackSpace) str+="BackSpace";
		else if(k == Esc) str+="Esc";
		else str+=k.c;
	}

	return str;
}

}}
