#pragma once
#include "common.hpp"
#include "../gta/fwddec.hpp"
#include "../gta/enums.hpp"
#include "../gta/function_types.hpp"

namespace TimeWaste
{
struct Vector2
{
	float x{};
	float y{};
};

class pointers
{
public:
	explicit pointers();
	~pointers();

public:
	HWND m_hwnd{};

	eGameState* m_game_state{};
	bool* m_is_session_started{};
	int* m_get_vehicle_sell{};

	CPedFactory** m_ped_factory{};
	CNetworkPlayerMgr** m_network_player_mgr{};

	rage::scrNativeRegistrationTable* m_native_registration_table{};
	rage::get_native_handler_t m_get_native_handler{};
	rage::fix_vectors_t m_fix_vectors{};

	rage::atArray<GtaThread*>* m_script_threads{};
	rage::scrProgramTable* m_script_program_table{};
	rage::run_script_threads_t m_run_script_threads{};
	std::int64_t** m_script_globals{};

	CGameScriptHandlerMgr** m_script_handler_mgr{};

	IDXGISwapChain** m_swapchain{};
};

inline pointers* g_pointers{};
}
