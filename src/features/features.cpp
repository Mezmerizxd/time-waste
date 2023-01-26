#include "../natives.hpp"
#include "../script/script.hpp"
#include "features.hpp"
#include "../gta/lists.hpp"
#include "../logger.hpp"

namespace TimeWaste
{
#pragma region "WEAPON"
void Features::GiveAllWeaponsToPlayer(uint32_t Player)
{
	Ped player = Player;
	for (int i = 0; i < (sizeof(WEAPON_HASH_LIST) / 4); i++)
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(
		player, WEAPON_HASH_LIST[i], 9999, 0);
	LOG_INFO("Gave all weapons to player");
}

void Features::EnableWeaponTeleportBullets()
{
	if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID())
		&& PED::IS_PED_SHOOTING_IN_AREA)
	{
		Vector3 iCoord;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(
			PLAYER::PLAYER_PED_ID(), &iCoord))
		{
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), iCoord.x,
			iCoord.y, iCoord.z + 1, 0, 0, 1, 1);
		}
	}
}
#pragma endregion

void Features::script_init()
{
	// Functions that will run once
}

void Features::script_on_tick()
{
	Entity plyrPedId = PLAYER::PLAYER_PED_ID();
	Player plyrId    = PLAYER::PLAYER_ID();

#pragma region "SELF"
	// Godmode
	if (self_godmode)
	{
		ENTITY::SET_ENTITY_INVINCIBLE(plyrPedId, true);
	}
	else
	{
		ENTITY::SET_ENTITY_INVINCIBLE(plyrPedId, false);
	}
	// Never Wanted
	if (self_never_wanted)
	{
		PLAYER::CLEAR_PLAYER_WANTED_LEVEL(plyrId);
		PLAYER::SET_MAX_WANTED_LEVEL(0);
		PLAYER::SET_POLICE_IGNORE_PLAYER(plyrPedId, self_never_wanted);
		PLAYER::SET_EVERYONE_IGNORE_PLAYER(plyrPedId, self_never_wanted);
		PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(
		plyrPedId, self_never_wanted);
	}
	// No Ragdoll
	if (self_no_ragdoll)
	{
		PED::SET_PED_CAN_RAGDOLL(plyrPedId, false);
	}
	else
	{
		PED::SET_PED_CAN_RAGDOLL(plyrPedId, true);
	}
	// Super Jump
	if (self_super_jump)
	{
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(plyrPedId);
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(plyrId);
	}
	// Fast Run
	if (self_fast_run)
	{
		PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(plyrId, 2.0f);
	}
	else
	{
		PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(plyrId, 1.0f);
	}
#pragma endregion

#pragma region "WEAPON"
	// Teleport Bullets
	if (weapon_teleport_bullets)
	{
		EnableWeaponTeleportBullets();
	}
#pragma endregion
}

void Features::script_func()
{
	g_features.script_init();

	while (true)
	{
		g_features.script_on_tick();
		script::get_current()->yield();
	}
}
}
