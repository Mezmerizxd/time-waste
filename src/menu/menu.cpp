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
        g_interface.AddSubmenu<RegularSubmenu>("Home", Home, [](RegularSubmenu *sub) {
            sub->AddOption<SubOption>("Self", nullptr, Self);
            sub->AddOption<SubOption>("Extra", nullptr, Self);
        });

        // Self
        g_interface.AddSubmenu<RegularSubmenu>("Self", Self, [](RegularSubmenu *sub) {
            sub->AddOption<BoolOption<bool>>("Godmode", nullptr, &g_features.self_godmode, BoolDisplay::DefaultToggles);
        });

        // Extra
        g_interface.AddSubmenu<RegularSubmenu>("Extra", Extra, [](RegularSubmenu *sub) {
            sub->AddOption<BoolOption<bool>>("Same Godmode", nullptr, &g_features.self_godmode, BoolDisplay::DefaultToggles);
        });
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

