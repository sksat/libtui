#include "screen.hpp"
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

// エスケープシーケンス・CSIシーケンス 参考情報
// https://ttssh2.osdn.jp/manual/ja/about/ctrlseq.html

namespace tui { namespace screen {
	const info get_info(){
		info i;
		winsize ws;
		if(ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
			i.width = i.height = 0;
		else{
			i.width = ws.ws_col;
			i.height= ws.ws_row;
		}
	}

	void esc(const std::string &command){
		printf("\e%s", command.c_str());
	}
	void csi(const std::string &command){
		printf("\e[%s", command.c_str());
	}

	void clear(){ printf("\e[1;1H\e[2J"); }
	void flush(){ fflush(0); }

	void push_title(){ csi("22;0;0t"); }
	void pop_title(){  csi("23;0;0t"); }

	// enter_ca_mode,exit_ca_modeは端末エミュレータによって違うらしいので要調査．
	// termcap	ti:enter, smcup:exit
	// terminfo	te:enter, rmcup:exit
	void enter_ca_mode(){ csi("?1049h"); }
	void exit_ca_mode(){  csi("?1049l"); }
}}
