#ifndef TUI_CONFIG_HPP_
#define TUI_CONFIG_HPP_

namespace tui {
	struct config {
		constexpr config() :
			echo(true), canonical(true), signal(true) {}
		constexpr config(bool e, bool c, bool s) :
			echo(e), canonical(c), signal(s) {}

		template<typename Conf>
		constexpr bool operator==(Conf c){
			return true;
		}

		bool echo, canonical, signal;

		static constexpr config raw(){ return config(false, false, false); }

		static config now();
		static void set(const config&);
		void set(){ config::set(*this); }
		static void fix();
	};
}

#endif
