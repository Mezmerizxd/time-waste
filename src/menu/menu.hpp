#pragma once
#include "../common.hpp"

namespace TimeWaste
{
    enum Submenu : std::uint32_t {
		Home,
		Self,
		Extra
	};

	class Menu
	{
	public:
		void menu();

        void script_init();
		void script_on_tick();
		static void script_func();
	};

	inline Menu g_menu;
}
