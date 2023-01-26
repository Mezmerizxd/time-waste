#include "menu.hpp"
#include "../natives.hpp"
#include "../bigbase/RegularOption.hpp"
#include "../bigbase/SubOption.hpp"
#include "../bigbase/BoolOption.hpp"
#include "../bigbase/ChooseOption.hpp"
#include "../bigbase/NumberOption.hpp"
#include "../bigbase/AbstractSubmenu.hpp"
#include "../bigbase/RegularSubmenu.hpp"
#include "../bigbase/Timer.hpp"
#include "../script/script.hpp"
#include "../features/features.hpp"

namespace TimeWaste
{
void Menu::menu()
{
	using namespace BigBase;

	// Home
	g_interface.AddSubmenu<RegularSubmenu>("Home", Home,
	[](RegularSubmenu* sub)
	{
		sub->AddOption<SubOption>("Self", nullptr, Self);
		sub->AddOption<SubOption>("Lobby", nullptr, Lobby);
		sub->AddOption<SubOption>("Weapon", nullptr, Weapon);
		sub->AddOption<SubOption>("Vehicle", nullptr, Vehicle);
		sub->AddOption<SubOption>("Teleport", nullptr, Teleport);
		sub->AddOption<SubOption>("World", nullptr, World);
		sub->AddOption<SubOption>("Object Spawner", nullptr, ObjectSpawner);
		sub->AddOption<SubOption>("Recovery", nullptr, Recovery);
		sub->AddOption<SubOption>("Lua", nullptr, Lua);
		sub->AddOption<SubOption>("Settings", nullptr, Settings);
	});

	// Self
	g_interface.AddSubmenu<RegularSubmenu>("Self", Self,
	[](RegularSubmenu* sub)
	{
		sub->AddOption<BoolOption<bool>>("Godmode", nullptr,
		&g_features.self_godmode, BoolDisplay::DefaultToggles);
		sub->AddOption<BoolOption<bool>>("Never Wanted", nullptr,
		&g_features.self_never_wanted, BoolDisplay::DefaultToggles);
		sub->AddOption<BoolOption<bool>>("No Ragdoll", nullptr,
		&g_features.self_no_ragdoll, BoolDisplay::DefaultToggles);
		sub->AddOption<BoolOption<bool>>("Super Jump", nullptr,
		&g_features.self_super_jump, BoolDisplay::DefaultToggles);
		sub->AddOption<BoolOption<bool>>("Fast Run", nullptr,
		&g_features.self_fast_run, BoolDisplay::DefaultToggles);
	});

	// Lobby
	g_interface.AddSubmenu<RegularSubmenu>(
	"Lobby", Lobby, [](RegularSubmenu* sub) {});

	// Weapon
	g_interface.AddSubmenu<RegularSubmenu>("Weapon", Weapon,
	[](RegularSubmenu* sub)
	{
		sub->AddOption<RegularOption>("Give All Weapons", nullptr,
		[]()
		{
			g_features.GiveAllWeaponsToPlayer(PLAYER::PLAYER_PED_ID());
		});
		sub->AddOption<SubOption>("Bullets", nullptr, WeaponBullets);
	});

	// WeaponBullets
	g_interface.AddSubmenu<RegularSubmenu>("Bullets", WeaponBullets,
	[](RegularSubmenu* sub)
	{
		sub->AddOption<BoolOption<bool>>("Teleport", nullptr,
		&g_features.weapon_teleport_bullets, BoolDisplay::DefaultToggles);
	});

	// Vehicle
	g_interface.AddSubmenu<RegularSubmenu>(
	"Vehicle", Vehicle, [](RegularSubmenu* sub) {});

	// Teleport
	g_interface.AddSubmenu<RegularSubmenu>(
	"Teleport", Teleport, [](RegularSubmenu* sub) {});

	// World
	g_interface.AddSubmenu<RegularSubmenu>(
	"World", World, [](RegularSubmenu* sub) {});

	// ObjectSpawner
	g_interface.AddSubmenu<RegularSubmenu>(
	"Object Spawner", ObjectSpawner, [](RegularSubmenu* sub) {});

	// Recovery
	g_interface.AddSubmenu<RegularSubmenu>(
	"Recovery", Recovery, [](RegularSubmenu* sub) {});

	// Lua
	g_interface.AddSubmenu<RegularSubmenu>(
	"Lua", Lua, [](RegularSubmenu* sub) {});

	// Settings
	g_interface.AddSubmenu<RegularSubmenu>(
	"Settings", Settings, [](RegularSubmenu* sub) {});
}

void Menu::script_init()
{
	menu();
}

void Menu::script_on_tick()
{
	g_interface.Tick();
}

void Menu::script_func()
{
	g_menu.script_init();

	while (true)
	{
		g_menu.script_on_tick();
		script::get_current()->yield();
	}
}
}
