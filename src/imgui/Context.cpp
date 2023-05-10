#include "Context.hpp"

#include <SDL.h>

#include "rendering/Device.hpp"

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui/Icons.hpp"
#include "imgui_impl_sdl.h"

#include <filesystem>
#include <unordered_map>

#define HEX_ARGB( v ) ImColor( ( int )( v >> 16 ) & 0xFF, ( int )( v >> 8 ) & 0xFF, ( int )( v >> 0 ) & 0xFF, ( int )( v >> 24 ) & 0xFF )

namespace ImGui
{
    Context::Context()
    {
#ifdef _DEBUG
        auto path = std::filesystem::current_path() / "..";
        ::SetCurrentDirectoryW( path.c_str() );
#endif

        ImGui::CreateContext();

        auto & style = ImGui::GetStyle();
        style = ImGuiStyle{};

        style.Alpha = 1.0f;
        style.AntiAliasedLines = true;
        style.AntiAliasedFill = true;
        style.AntiAliasedLinesUseTex = true;

        style.WindowTitleAlign = { 0.5f, 0.5f };
        style.WindowPadding = { 10.0f, 10.0f };

        style.WindowBorderSize = 1.0f;
        style.ChildBorderSize = 1.0f;
        style.FrameBorderSize = 1.0f;
        style.TabBorderSize = 1.0f;

        style.DisplayWindowPadding = { 0.0f, 0.0f };
        style.DisplaySafeAreaPadding = { 0.0f, 0.0f };
        style.SelectableTextAlign = { 0.0f, 0.5f };

        style.ItemSpacing = { 5.0f, 1.0f };
        style.ItemInnerSpacing = { 2.0f, 2.0f };
        style.IndentSpacing = 10.0f;

        style.FramePadding = { 5.0f, 4.0f };
        style.FrameRounding = 4.0f;

        style.ScrollbarSize = 16.0f;

        style.TabRounding = style.FrameRounding;

        style.GrabRounding = 4.0f;
        style.GrabMinSize = 8.0f;

        ImGui::StyleColorsDark();

        static std::unordered_map< int, ImColor > g_darkThemeColors =
        {
            { ImGuiCol_Button,              HEX_ARGB( 0xFF383838 ) },
            { ImGuiCol_ButtonHovered,       { 75,   75,     75, 255 } },
            { ImGuiCol_ButtonActive,        { 25,   25,     25, 255 } },

            { ImGuiCol_Text,                HEX_ARGB( 0xCCEFEFEF ) },
            { ImGuiCol_TextDisabled,        HEX_ARGB( 0xFF424242 ) },

            { ImGuiCol_Border,              HEX_ARGB( 0xFF161616 ) },
            { ImGuiCol_BorderShadow,        HEX_ARGB( 0x11FFFFFF ) },

            { ImGuiCol_WindowBg,            HEX_ARGB( 0xFF121212 ) },
            { ImGuiCol_MenuBarBg,           HEX_ARGB( 0xFF121212 ) },
            { ImGuiCol_PopupBg,             HEX_ARGB( 0xFF222222 ) },
            { ImGuiCol_ChildBg,             HEX_ARGB( 0xFF242424 ) },
            { ImGuiCol_ModalWindowDimBg,    HEX_ARGB( 0x00000000 ) },

            { ImGuiCol_FrameBg,             HEX_ARGB( 0xFF383838 ) },
            { ImGuiCol_FrameBgActive,       { 77,   77,     77, 255 } },
            { ImGuiCol_FrameBgHovered,      { 93,   93,     93, 255 } },

            { ImGuiCol_Header,              { 77,   77,     77, 255 } },
            { ImGuiCol_HeaderActive,        { 88,   88,     88, 255 } },
            { ImGuiCol_HeaderHovered,       { 99,   99,     99, 255 } },

            { ImGuiCol_SliderGrab,          { 221,  220,    231, 255 } },

            { ImGuiCol_TitleBg,             HEX_ARGB( 0xFF1A1A1A ) },
            { ImGuiCol_TitleBgActive,       HEX_ARGB( 0xFF1A1A1A ) },
            { ImGuiCol_TitleBgCollapsed,    HEX_ARGB( 0xFF1A1A1A ) },

            { ImGuiCol_Tab,                 { 29,   31,     33, 255 } },
            { ImGuiCol_TabActive,           { 51,   51,     51, 255 } },
            { ImGuiCol_TabHovered,          { 77,   77,     77, 255 } },
            { ImGuiCol_TabUnfocused,        { 23,   23,     23, 255 } },
            { ImGuiCol_TabUnfocusedActive,  { 51,   51,     51, 255 } },
        };

        for ( auto && it : g_darkThemeColors )
        {
            style.Colors[ it.first ] = it.second;
        }

        style.Colors[ ImGuiCol_ResizeGrip ] = style.Colors[ ImGuiCol_FrameBg ];
        style.Colors[ ImGuiCol_Separator ] = style.Colors[ ImGuiCol_Border ];

        //float scale = ImGui::GetMainViewport()->DpiScale;
        //if ( ImGui::GetPlatformIO().Platform_GetWindowDpiScale )
        //    scale = ImGui::GetPlatformIO().Platform_GetWindowDpiScale( ImGui::GetMainViewport() );
        //style.ScaleAllSizes( scale );

        ImFontConfig config = {};
        config.RasterizerMultiply = 1.3f;
        config.OversampleH = 4;
        config.OversampleH = 4;

        ImGui::GetIO().Fonts->AddFontFromFileTTF( "assets/fonts/Roboto-Regular.ttf", 18.0f, &config );

        config.MergeMode = true;
        config.PixelSnapH = true;

        static const ImWchar FAS_GLYPH_RANGE[] =
        {
            ICON_MIN_FA, ICON_MAX_FA, 0
        };

        ImGui::GetIO().Fonts->AddFontFromFileTTF( "assets/fonts/fa-solid-900.ttf", 18.0f, &config, FAS_GLYPH_RANGE );
    }

    Context::~Context()
    {
        ImGui::DestroyContext();
    }

    bool Context::PollEvents( lst::Device & device )
    {
        SDL_Event evt{};
        while ( SDL_PollEvent( &evt ) )
        {
            ImGui_ImplSDL2_ProcessEvent( &evt );
            if ( evt.type == SDL_QUIT )
                return false;

            if ( evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_CLOSE )
                return false;

            if ( evt.type == SDL_WINDOWEVENT && evt.window.event == SDL_WINDOWEVENT_RESIZED )
            {
                device.ResizeBackBuffer();
            }
        }

        return true;
    }
}
