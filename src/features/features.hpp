#pragma once
#include "../common.hpp"

namespace TimeWaste
{
	class Features
	{
	public:

        void script_init();
		void script_on_tick();
		static void script_func();

    public:
        // Self
        bool self_godmode{};
	};

	inline Features g_features;
    inline std::unique_ptr<TimeWaste::Features> g_Features;
}
