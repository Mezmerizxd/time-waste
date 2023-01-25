#pragma once
#include "../common.hpp"

namespace TimeWaste
{
    enum Submenu : std::uint32_t {
		Home,
		Self,
		Lobby,
		Weapon,
		Vehicle,
		Teleport,
		World,
		ObjectSpawner,
		Recovery,
		Lua,
		Settings,
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
