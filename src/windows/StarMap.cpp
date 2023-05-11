#include "StarMap.hpp"

#include "api/System.hpp"

#include "imgui.h"
#include "imgui_internal.h"

#include "imgui/widgets/imgui_canvas.h"
#include "imgui/Icons.hpp"

#include <format>

namespace lst
{
    constexpr auto GRID_SIZE = ImVec2{ 100.0f, 100.0f };

    void StarMap::DrawWindow()
    {
        //static auto s_agent = lst::api::GetAgentInfo( "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZGVudGlmaWVyIjoiTE1YIiwiaWF0IjoxNjgzNzUwNDEyLCJzdWIiOiJhZ2VudC10b2tlbiJ9.WLJzLcF5KyKVJTnHzLYx507yKWWV-ceTgcYJHM8nOUnZ0NXA62h773I-3Tyg5hNlQFTCzrqYxlh7_J7qp09vzHZw8nOb01YKgznZodf62_MktfE_3O3R1FT355AWHlH7jVHZ2GE17xJSe8jqGRwT5HO-_8wVEW5NEEVkTMkQQz0mKH53SZ3Oczf3fmnb3FpA7LP2Ak2F1cq6ueqo7eRkR2cRa8Ewimyk5RbBhzUw2_hjyZTnHUAwPTsVwidJ3mIMavf84u6gYHUge0OaIAPrYXys_BF7OHhwcDbfGbAf4YltADp5iNtxGFXEpZpRWlxCYsrudbkkFaVs8h4fUi-OXFYJn8zyUixYO8DZDXRWaZ0u-avU55lxK7TgCktgOzZxLg5fLY0i6wt9pdz_bbzXKHhA8WSiL7okXBZfOga8vMWCibfg1C_NElYgEpfHuS80RkQC9GSIyHHR7XiR-j-Ugl6cqVA0666iNHNBs4DBSEqxZyIYeEUa7lPdh4O0PeTX" );
        //if ( !s_agent.has_value() )
        //{
        //    if ( ImGui::Button( ICON_FA_SQUARE_PLUS, { 64.0f, 64.0f } ) )
        //    {
        //        ImGui::OpenPopup( "Register agent" );
        //    }

        //    if ( ImGui::BeginPopupModal( "Register agent" ) )
        //    {
        //        DrawRegisterTab();
        //        ImGui::EndPopup();
        //    }
        //}

        //auto & agent = s_agent.value();
        //if ( ImGui::Button( agent.symbol.c_str(), { 64.0f, 64.0f } ) )
        //{
        //}

        //ImGui::SameLine();

        //ImGui::BeginGroup();
        //{
        //    ImGui::SetNextItemWidth( 256.0f );
        //    ImGui::Text( ICON_FA_HOUSE" Headquarters:" );

        //    ImGui::SameLine();

        //    ImGui::Text( agent.headquarters.c_str() );

        //    ImGui::SetNextItemWidth( 256.0f );
        //    ImGui::Text( ICON_FA_DOLLAR_SIGN" Credits:" );

        //    ImGui::SameLine();

        //    ImGui::Text( std::to_string( agent.credits ).c_str() );
        //}
        //ImGui::EndGroup();

        //if ( ImGui::BeginTabBar( "##content" ) )
        //{
        //    if ( ImGui::BeginTabItem( "System" ) )
        //    {
        //        DrawSystemCanvas();
        //        ImGui::EndTabItem();
        //    }

        //    ImGui::EndTabBar();
        //}

        static std::unordered_map< std::string, float > s_systemSize =
        {
            { "NEUTRON_STAR", 1.0f },
            { "RED_STAR", 1.0f },
            { "ORANGE_STAR", 1.0f },
            { "BLUE_STAR", 1.0f },
            { "YOUNG_STAR", 1.0f },
            { "WHITE_DWARF", 1.0f },
            { "BLACK_HOLE", 1.0f },
            { "HYPERGIANT", 1.0f },
            { "NEBULA", 1.0f },
            { "UNSTABLE", 1.0f },
        };

        static std::unordered_map< std::string, float > s_waypointSize =
        {
            { "PLANET", 1.0f },
            { "GAS_GIANT", 1.0f },
            { "MOON", 1.0f },
            { "ORBITAL_STATION", 1.0f },
            { "JUMP_GATE", 1.0f },
            { "ASTEROID_FIELD", 1.0f },
            { "NEBULA", 1.0f },
            { "DEBRIS_FIELD", 1.0f },
            { "GRAVITY_WELL", 1.0f },
        };

        static auto s_systems = lst::api::GetSystems();
        if ( !s_systems.has_value() )
            ImGui::TextColored( { 1.0f, 0.0f, 0.0f,1.0f }, "ERROR: failed to retrieve systems list: %s", s_systems.error().message() );
        else
        {
            if ( ImGui::IsMouseDragging( ImGuiMouseButton_Middle ) )
            {
                m_canvas.SetView( m_canvas.ViewOrigin() + ImGui::GetMouseDragDelta( ImGuiMouseButton_Middle ), m_canvas.ViewScale() );
                ImGui::ResetMouseDragDelta( ImGuiMouseButton_Middle );
            }

            if ( ImAbs( ImGui::GetIO().MouseWheel ) > 0.0f )
            {
                m_canvas.SetView( m_canvas.ViewOrigin(), ImMax( 0.1f, m_canvas.ViewScale() + ( ImGui::GetIO().MouseWheel ) / 10.0f ) );
            }

            if ( !m_canvas.Begin( "##system", ImGui::GetContentRegionAvail() ) )
                return;

            auto viewPos = m_canvas.ViewRect().Min;
            auto viewSize = m_canvas.ViewRect().GetSize();

            auto offset = m_canvas.ViewOrigin() * ( 1.0f / m_canvas.ViewScale() );
            for ( float x = fmodf( offset.x, GRID_SIZE.x ); x < viewSize.x; x += GRID_SIZE.x )
                ImGui::GetWindowDrawList()->AddLine( ImVec2( x - GRID_SIZE.x / 2.0f, 0.0f ) + viewPos, ImVec2( x - GRID_SIZE.x / 2.0f, viewSize.y ) + viewPos, ImColor( 1.0f, 1.0f, 1.0f, 0.25f ), 1.0f );

            for ( float y = fmodf( offset.y, GRID_SIZE.y ); y < viewSize.y; y += GRID_SIZE.y )
                ImGui::GetWindowDrawList()->AddLine( ImVec2( 0.0f, y - GRID_SIZE.y / 2.0f ) + viewPos, ImVec2( viewSize.x, y - GRID_SIZE.y / 2.0f ) + viewPos, ImColor( 1.0f, 1.0f, 1.0f, 0.25f ), 1.0f );

            auto & systems = s_systems.value();
            for ( auto & system : systems )
            {
                auto origin = ImVec2{ ( float )system.x, ( float )system.y } *GRID_SIZE;

                {
                    ImGui::PushStyleColor( ImGuiCol_Text, ( ImU32 )ImColor( 1.0f, 1.0f, 0.0f, 1.0f ) );
                    ImGui::RenderText( origin + ImVec2{ -ImGui::GetTextLineHeight() / 2.0f, -ImGui::GetTextLineHeight() / 2.0f }, std::format( ICON_FA_SUN ).c_str() );
                    ImGui::PopStyleColor();
                }

                for ( auto & waypoint : system.waypoints )
                {
                    auto pos = origin + ImVec2{ ( float )waypoint.x, ( float )waypoint.y } *GRID_SIZE / 20.0f;

                    if ( waypoint.type == "MOON" )
                    {
                        pos -= ImVec2{ 15.0f, 15.0f };

                        ImGui::SetWindowFontScale( 0.5f );
                        ImGui::RenderText( pos + ImVec2{ -ImGui::GetTextLineHeight() / 2.0f, -ImGui::GetTextLineHeight() / 2.0f }, ICON_FA_MOON );
                        ImGui::SetWindowFontScale( 1.0f );
                    }
                    else if ( waypoint.type == "PLANET" || waypoint.type == "GAS_GIANT" )
                    {
                        float radius = ImSqrt( ImLengthSqr( origin - pos ) );

                        ImGui::GetWindowDrawList()->AddCircle( origin, radius, ImColor( 0.3f, 0.3f, 0.0f, 1.0f ) );
                        ImGui::RenderText( pos + ImVec2{ -ImGui::GetTextLineHeight() / 2.0f, -ImGui::GetTextLineHeight() / 2.0f }, ICON_FA_GLOBE );
                    }
                    else
                    {
                        ImGui::RenderBullet( ImGui::GetWindowDrawList(), pos, ImColor( 1.0f, 0.0f, 0.0f, 1.0f ) );
                    }

                }
            }

            m_canvas.End();
        }
    }

}

