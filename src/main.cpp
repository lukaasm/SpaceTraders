#include <windows.h>

#include <stdio.h>
#include <SDL.h>

#include "rendering/Device.hpp"
#include "windows/Application.hpp"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui/Context.hpp"
#include "imgui/Icons.hpp"
#include "imgui/widgets/imgui_canvas.h"

#include <string>

int WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
    ::ImGui_ImplWin32_EnableDpiAwareness();

    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER );

    // Setup window
    auto windowFlags = ( SDL_WindowFlags )( SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI );
    auto * window = SDL_CreateWindow( "SpaceTraders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, windowFlags );

    {
        ImGui::Context context;

        lst::Device device;
        if ( !device.Initialize( window ) )
            return EXIT_FAILURE;

        context.Initialize();

        lst::Application application;
        while ( context.PollEvents( device ) )
        {
            device.BeginFrame();

            ImGui::NewFrame();

            ImGui::SetNextWindowPos( ImGui::GetMainViewport()->Pos );
            ImGui::SetNextWindowSize( ImGui::GetMainViewport()->Size );
            if ( ImGui::Begin( "##application", nullptr, ImGuiWindowFlags_NoDecoration ) )
            {
                application.DrawWindow();
            }

            ImGui::End();

            device.EndFrame();
        }
    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}
