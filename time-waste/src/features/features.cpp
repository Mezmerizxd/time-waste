#include "../natives.hpp"
#include "../script/script.hpp"
#include "features.hpp"

namespace TimeWaste
{
    void Features::script_init()
    {
        // Functions that will run once
    }

    void Features::script_on_tick()
    {
        // Functions that will run continuously
        if (self_godmode) { ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true); }
		else { ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false); }
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