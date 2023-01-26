#pragma once
#include "../common.hpp"

namespace TimeWaste
{
class Features
{
public:
	void GiveAllWeaponsToPlayer(uint32_t Player);
	void EnableWeaponTeleportBullets();

	void script_init();
	void script_on_tick();
	static void script_func();

public:
	Entity plyrPedId{};
	Player plyrId{};

	// Self
	bool self_godmode{ false };
	bool self_never_wanted{ false };
	bool self_no_ragdoll{ false };
	bool self_super_jump{ false };
	bool self_fast_run{ false };

	// Weapon
	bool weapon_teleport_bullets{ false };
};

inline Features g_features;
inline std::unique_ptr<TimeWaste::Features> g_Features;
}
