#include "../natives.hpp"
#include "../script/script.hpp"
#include "features.hpp"
#include "../gta/lists.hpp"
#include "../logger.hpp"

namespace TimeWaste
{
    void Features::GiveAllWeaponsToPlayer(uint32_t Player)
    {
        Ped player = Player;
        for (int i = 0; i < (sizeof(WEAPON_HASH_LIST) / 4); i++)
		    WEAPON::GIVE_DELAYED_WEAPON_TO_PED(player, WEAPON_HASH_LIST[i], 9999, 1);
        LOG_INFO("Gave all weapons to player");
    }

    void Features::script_init()
    {
        // Functions that will run once   
    }

    void Features::script_on_tick()
    {
        Entity plyrPedId = PLAYER::PLAYER_PED_ID(); 
        Player plyrId = PLAYER::PLAYER_ID();

        if (self_godmode) { ENTITY::SET_ENTITY_INVINCIBLE(plyrPedId, true); }
		else { ENTITY::SET_ENTITY_INVINCIBLE(plyrPedId, false); }

        if (self_never_wanted) { PLAYER::CLEAR_PLAYER_WANTED_LEVEL(plyrId); PLAYER::SET_MAX_WANTED_LEVEL(0); PLAYER::SET_POLICE_IGNORE_PLAYER(plyrPedId, self_never_wanted); PLAYER::SET_EVERYONE_IGNORE_PLAYER(plyrPedId, self_never_wanted); PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(plyrPedId, self_never_wanted);  }

        if (self_no_ragdoll) { PED::SET_PED_CAN_RAGDOLL(plyrPedId, false); }
		else { PED::SET_PED_CAN_RAGDOLL(plyrPedId, true); }

        if (self_super_jump) { GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(plyrPedId); GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(plyrId); }

        if (self_fast_run) { PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(plyrId, self_fast_run); }
		else { PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(plyrId, 1.0f); }
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