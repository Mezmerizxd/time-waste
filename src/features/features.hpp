#pragma once
#include "../common.hpp"

namespace TimeWaste
{
	class Features
	{
	public:
		void GiveAllWeaponsToPlayer(uint32_t Player);

        void script_init();
		void script_on_tick();
		static void script_func();

    public:
		Entity plyrPedId{};
		Player plyrId{};

        // Self
        bool self_godmode{};
		bool self_never_wanted{};
		bool self_no_ragdoll{};
		bool self_super_jump{};
		bool self_fast_run{};
	};

	inline Features g_features;
    inline std::unique_ptr<TimeWaste::Features> g_Features;
}
