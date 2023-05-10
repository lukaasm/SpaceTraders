#include <windows.h>

#include "imgui.h"
#include <stdio.h>
#include <SDL.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "rendering/Device.hpp"
#include "api/Agent.hpp"
#include "imgui/Context.hpp"
#include "imgui/Icons.hpp"

#include <string>
#include "imgui/widgets/imgui_canvas.h"
#include "api/System.hpp"

static void DrawRegisterTab()
{
    static lst::api::Result<lst::api::Registrar> s_result;
    ImGui::Text( "Call sign:" );

    ImGui::SetNextItemWidth( -FLT_MIN );

    static std::string s_symbol( 2048, 0 );
    ImGui::InputText( "##symbol", ( char * )s_symbol.c_str(), s_symbol.size() );

    static std::string s_faction = "COSMIC";

    ImGui::Text( "Faction:" );

    ImGui::SetNextItemWidth( -FLT_MIN );
    if ( ImGui::BeginCombo( "##faction", s_faction.c_str() ) )
    {
        for ( auto faction : { "COSMIC", "VOID", "GALACTIC", "QUANTUM", "DOMINION" } )
        {
            if ( ImGui::Selectable( faction ) )
                s_faction = faction;
        }

        ImGui::EndCombo();
    }

    if ( ImGui::Button( "Register", { -FLT_MIN, 0.0f } ) )
    {
        s_result = lst::api::RegisterAgent( s_symbol.c_str(), s_faction );
    }
}

static void DrawSystemCanvas()
{
    static ImGuiEx::Canvas s_canvas;

    static auto s_systems = lst::api::GetSystems();
    if ( !s_systems.has_value() )
        ImGui::TextColored( { 1.0f, 0.0f, 0.0f,1.0f }, "ERROR: failed to retrieve systems list: %s", s_systems.error().message() );
    else
    {
        if ( ImGui::IsMouseDragging( ImGuiMouseButton_Middle ) )
        {
            s_canvas.SetView( s_canvas.ViewOrigin() + ImGui::GetMouseDragDelta( ImGuiMouseButton_Middle ), s_canvas.ViewScale() );
            ImGui::ResetMouseDragDelta( ImGuiMouseButton_Middle );
        }

        if ( ImAbs( ImGui::GetIO().MouseWheel ) > 0.0f )
        {
            s_canvas.SetView( s_canvas.ViewOrigin(), ImMax( 0.1f, s_canvas.ViewScale() + ( ImGui::GetIO().MouseWheel ) / 10.0f ) );
        }

        if ( s_canvas.Begin( "##system", ImGui::GetContentRegionAvail() ) )
        {
            constexpr auto SYSTEM_SIZE = ImVec2{ 75.0f, 75.0f };

            auto & systems = s_systems.value();
            for ( auto & system : systems )
            {
                {
                    auto pos = ImVec2{ ( float )system.x, ( float )system.y } *SYSTEM_SIZE;
                    {
                        ImGui::PushStyleColor( ImGuiCol_Text, ( ImU32 )ImColor( 1.0f, 1.0f, 0.0f, 1.0f ) );
                        ImGui::RenderText( pos + ImVec2{ 10.0f, -ImGui::GetTextLineHeight() / 2.0f }, std::format( ICON_FA_SUN" {}", system.symbol ).c_str() );
                        ImGui::PopStyleColor();
                    }
                    ImGui::RenderText( pos + ImVec2{ 15.0f, ImGui::GetTextLineHeight() }, system.type.c_str() );
                }

                for ( auto & waypoint : system.waypoints )
                {
                    auto pos = ImVec2{ ( float )waypoint.x, ( float )waypoint.y } *SYSTEM_SIZE;

                    ImGui::RenderText( pos + ImVec2{ 10.0f, -ImGui::GetTextLineHeight() / 2.0f }, waypoint.symbol.c_str() );
                    ImGui::RenderText( pos + ImVec2{ 15.0f, ImGui::GetTextLineHeight() }, waypoint.type.c_str() );

                    ImGui::RenderBullet( ImGui::GetWindowDrawList(), pos, ImColor( 1.0f, 0.0f, 0.0f, 1.0f ) );
                }
            }

            s_canvas.End();
        }
    }
}
int WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER );

    // Setup window
    auto windowFlags = ( SDL_WindowFlags )( SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI );
    auto * window = SDL_CreateWindow( "SpaceTraders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, windowFlags );

    {
        ImGui::Context context;

        lst::Device device;
        if ( !device.Initialize( window ) )
            return EXIT_FAILURE;

        while ( context.PollEvents( device ) )
        {
            device.BeginFrame();

            ImGui::NewFrame();

            ImGui::SetNextWindowPos( ImGui::GetMainViewport()->Pos );
            ImGui::SetNextWindowSize( ImGui::GetMainViewport()->Size );
            if ( ImGui::Begin( "##application", nullptr, ImGuiWindowFlags_NoDecoration ) )
            {
                static auto s_agent = lst::api::GetAgentInfo( "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZGVudGlmaWVyIjoiTE1YIiwiaWF0IjoxNjgzNzUwNDEyLCJzdWIiOiJhZ2VudC10b2tlbiJ9.WLJzLcF5KyKVJTnHzLYx507yKWWV-ceTgcYJHM8nOUnZ0NXA62h773I-3Tyg5hNlQFTCzrqYxlh7_J7qp09vzHZw8nOb01YKgznZodf62_MktfE_3O3R1FT355AWHlH7jVHZ2GE17xJSe8jqGRwT5HO-_8wVEW5NEEVkTMkQQz0mKH53SZ3Oczf3fmnb3FpA7LP2Ak2F1cq6ueqo7eRkR2cRa8Ewimyk5RbBhzUw2_hjyZTnHUAwPTsVwidJ3mIMavf84u6gYHUge0OaIAPrYXys_BF7OHhwcDbfGbAf4YltADp5iNtxGFXEpZpRWlxCYsrudbkkFaVs8h4fUi-OXFYJn8zyUixYO8DZDXRWaZ0u-avU55lxK7TgCktgOzZxLg5fLY0i6wt9pdz_bbzXKHhA8WSiL7okXBZfOga8vMWCibfg1C_NElYgEpfHuS80RkQC9GSIyHHR7XiR-j-Ugl6cqVA0666iNHNBs4DBSEqxZyIYeEUa7lPdh4O0PeTX" );
                if ( !s_agent.has_value() )
                {
                    if ( ImGui::Button( ICON_FA_SQUARE_PLUS, { 64.0f, 64.0f } ) )
                    {
                        ImGui::OpenPopup( "Register agent" );
                    }

                    if ( ImGui::BeginPopupModal( "Register agent" ) )
                    {
                        DrawRegisterTab();
                        ImGui::EndPopup();
                    }
                }

                auto & agent = s_agent.value();
                if ( ImGui::Button( agent.symbol.c_str(), { 64.0f, 64.0f } ) )
                {
                }

                ImGui::SameLine();

                ImGui::BeginGroup();
                {
                    ImGui::SetNextItemWidth( 256.0f );
                    ImGui::Text( ICON_FA_HOUSE" Headquarters:" );

                    ImGui::SameLine();

                    ImGui::Text( agent.headquarters.c_str() );

                    ImGui::SetNextItemWidth( 256.0f );
                    ImGui::Text( ICON_FA_DOLLAR_SIGN" Credits:" );

                    ImGui::SameLine();

                    ImGui::Text( std::to_string( agent.credits ).c_str() );
                }
                ImGui::EndGroup();

                if ( ImGui::BeginTabBar( "##content" ) )
                {
                    if ( ImGui::BeginTabItem( "System" ) )
                    {
                        DrawSystemCanvas();
                        ImGui::EndTabItem();
                    }

                    ImGui::EndTabBar();
                }
            }

            ImGui::End();

            device.EndFrame();
        }
    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}
