#include "../common.hpp"
#include "gui.hpp"
#include "../script/script.hpp"
#include "../natives.hpp"
#include "../logger.hpp"
#include <imgui.h>

namespace TimeWaste
{
    void Gui::dx_on_tick()
    {
        if (ImGui::Begin("Time Waste", 0, ImVec2(530.0f, 800.0f)))
        {
            ImGui::Text("Hello, world!");
        }
        ImGui::End();
    }

	float defaultR = 0.3, defaultG = 0.3, defaultB = 0.3; 
	PurgeVec defaultColor = PurgeVec{ defaultR, defaultG, defaultB };
	ImVec4 defaultText = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	char PlateText[9] = { 0 };
	float ColWheelR, ColWheelG, ColWheelB; float ColWheel[3] = { ColWheelR, ColWheelG, ColWheelB };

    void Gui::dx_init()
    {
        auto& style = ImGui::GetStyle();
		style.WindowMinSize = { 630.0f, 400.0f };
		style.WindowPadding = { 10.f, 10.f };
		style.PopupRounding = 0.f;
		style.FramePadding = { 8.f, 4.f };
		style.ItemSpacing = { 10.f, 8.f };
		style.ItemInnerSpacing = { 6.f, 6.f };
		style.TouchExtraPadding = { 0.f, 0.f };
		style.IndentSpacing = 21.f;
		style.ScrollbarSize = 15.f;
		style.GrabMinSize = 8.f;
		style.WindowBorderSize = 1.f;
		style.ChildBorderSize = 0.f;
		style.PopupBorderSize = 1.f;
		style.FrameBorderSize = 0.f;
		style.TabBorderSize = 0.f;
		style.WindowRounding = 0.f;
		style.ChildRounding = 0.f;
		style.FrameRounding = 0.f;
		style.ScrollbarRounding = 0.f;
		style.GrabRounding = 0.f;
		style.TabRounding = 0.f;
		style.WindowTitleAlign = { 0.5f, 0.5f };
		style.ButtonTextAlign = { 0.5f, 0.5f };
		style.DisplaySafeAreaPadding = { 3.f, 3.f };

		auto& colors = style.Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 0.90f, 0.19f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.066f, 0.066f, 0.066f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.21f, 0.21f, 0.21f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.21f, 0.21f, 0.21f, 0.78f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.28f, 0.27f, 0.27f, 0.54f);
		colors[ImGuiCol_TitleBg] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 0.54f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.39f, 0.38f, 0.38f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.31f, 0.31f, 0.31f, 0.78f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.41f, 0.41f, 0.41f, 0.87f);
		colors[ImGuiCol_Header] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 0.31f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 0.37f);
		colors[ImGuiCol_HeaderActive] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 0.51f);
		colors[ImGuiCol_Separator] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.21f, 0.21f, 0.21f, 0.86f);
		colors[ImGuiCol_TabHovered] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 0.86f);
		colors[ImGuiCol_TabActive] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 0.86f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.10f, 0.10f, 0.10f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		colors[ImGuiCol_CheckMark] = ImVec4(defaultColor.x, defaultColor.y, defaultColor.z, 1.00f);
    }

    void Gui::script_init()
    {
        // ...
    }

    void Gui::script_on_tick()
    {
        if (g_gui.m_opened)
        {
            CONTROLS::DISABLE_CONTROL_ACTION(2, 1, true);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 2, true);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 14, true);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 15, true);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 16, true);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 17, true);
			CONTROLS::DISABLE_CONTROL_ACTION(2, 24, true);
        }
    }

    void Gui::script_func()
    {
        g_gui.script_init();
        LOG_INFO("GUI script initialized");

        while (true)
        {
            g_gui.script_on_tick();
            script::get_current()->yield();
        }
    }
}