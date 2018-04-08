#ifndef TUI_CONFIG_HPP_
#define TUI_CONFIG_HPP_

namespace tui {
	struct config {
		constexpr config() :
			echo(true), erace(true), canonical(true), signal(true) {}
		constexpr config(bool ec, bool er, bool c, bool s) :
			echo(ec), erace(er), canonical(c), signal(s) {}

		template<typename Conf>
		constexpr bool operator==(Conf c) const {
			return (c.echo == echo ||
				c.erace == erace ||
				c.canonical == canonical ||
				c.signal == signal);
		}

		bool echo, erace;
		bool canonical, signal;

		static constexpr config raw() {    return config(false, false, false, false); }
		static constexpr config password(){return config(false, true,  true,  true); }

		static config now();
		static void set(const config&);
		void set(){ config::set(*this); }
		static void fix();
	};
}

#endif
