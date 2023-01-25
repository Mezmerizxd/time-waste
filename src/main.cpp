#include "common.hpp"
#include "pointers/pointers.hpp"
#include "hooking/hooking.hpp"
#include "renderer/renderer.hpp"
#include "fiber_pool/fiber_pool.hpp"
#include "script_manager/script_manager.hpp"
#include "gui/gui.hpp"
#include "menu/menu.hpp"
#include "features/features.hpp"
#include "logger.hpp"
#include "natives.hpp"

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID)
{
    using namespace TimeWaste;

    if (reason == DLL_PROCESS_ATTACH) 
    {
        DisableThreadLibraryCalls(hmod);

        g_hmodule = hmod;
        g_main_thread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
        {
            // Initialize logger
            auto logger_instance = std::make_unique<logger>();
            LOG_INFO("Initialized logger");

            try 
            {
                // Initialize pointers instance and check if the game is ready
                auto pointers_instance = std::make_unique<pointers>();
                LOG_INFO("Initialized pointers");
                if (*g_pointers->m_game_state != eGameState::Playing)
                {
                    LOG_INFO("Waiting for game to start...");
                    do
                    {
                        std::this_thread::sleep_for(100ms);
                    } while (*g_pointers->m_game_state != eGameState::Playing);
                    LOG_INFO("Game started");
                }
                else
                {
                    LOG_INFO("Game already started");
                }

                // Initialize renderer instance
                auto renderer_instance = std::make_unique<renderer>();
				LOG_INFO("Renderer initialized.");

                // Initialize fiber pool instance
                auto fiber_pool_instance = std::make_unique<fiber_pool>(10);
				LOG_INFO("Fiber pool initialized.");

                // Initialize hooking instance
                auto hooking_instance = std::make_unique<hooking>();
				LOG_INFO("Hooking initialized.");

                // Register script functions
                g_script_manager.add_script(std::make_unique<script>(&Gui::script_func));
                g_script_manager.add_script(std::make_unique<script>(&Menu::script_func));
                g_script_manager.add_script(std::make_unique<script>(&Features::script_func));

                // Enable hooks
                g_hooking->enable();
				LOG_INFO("Hooking enabled.");

                while (g_running)
			    {
			    	if (GetAsyncKeyState(VK_END) & 0x8000)
			    		g_running = false;

                    g_hooking->ensure_dynamic_hooks();
			    	std::this_thread::sleep_for(10ms);
			    }

                // Disable hooks
                g_hooking->disable();

                std::this_thread::sleep_for(1000ms);

                // Unregister script functions
                g_script_manager.remove_all_scripts();

                // Uninitialize hooking instance
                hooking_instance.reset();
				LOG_INFO("Hooking uninitialized.");

                // Uninitialize fiber pool instance
                fiber_pool_instance.reset();
				LOG_INFO("Fiber pool uninitialized.");

                // Uninitialize renderer instance
                renderer_instance.reset();
				LOG_INFO("Renderer uninitialized.");

                // Uninitialize pointers instance
                pointers_instance.reset();
				LOG_INFO("Pointers uninitialized.");
            }
            catch (std::exception const &ex)
            {
                LOG_ERROR("Exception: {}", ex.what());
                MessageBoxA(nullptr, ex.what(), nullptr, MB_OK | MB_ICONEXCLAMATION);
            }

            LOG_INFO("Main thread exitting");
            logger_instance.reset();
            CloseHandle(g_main_thread);
            FreeLibraryAndExitThread(g_hmodule, 0);
        }, nullptr, 0, &g_main_thread_id);
    }
    return true;
}