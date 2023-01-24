#pragma once
#include "../common.hpp"
#include "../script/script.hpp"

namespace TimeWaste
{
	class script_manager
	{
	public:
		explicit script_manager() = default;
		~script_manager() = default;

		void add_script(std::unique_ptr<script> script);
		void remove_all_scripts();

		void tick();
	private:
		void tick_internal();
	private:
		std::recursive_mutex m_mutex;
		std::vector<std::unique_ptr<script>> m_scripts;
	};

	inline script_manager g_script_manager;
}
