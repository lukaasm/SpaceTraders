#include "Factions.hpp"

#include "api/Faction.hpp"

#include "imgui.h"

namespace lst
{
    void Factions::DrawWindow()
    {
        static auto s_factions = lst::api::GetFactions();
        if ( !s_factions.has_value() )
            return ImGui::Text( "Failed to acquire factions list!" );

        for ( auto & faction : s_factions.value() )
        {
            ImGui::PushStyleColor( ImGuiCol_ChildBg, ImGui::GetStyle().Colors[ ImGuiCol_WindowBg ] );
            if ( ImGui::BeginChild( faction.name.c_str(), { 400.0f, 450.f }, true ) )
            {
                ImGui::TreeNodeEx( faction.name.c_str(), ImGuiTreeNodeFlags_CollapsingHeader );

                ImGui::PushTextWrapPos( ImGui::GetContentRegionAvail().x );
                ImGui::TextWrapped( faction.description.c_str() );
                ImGui::PushTextWrapPos();
            }
            ImGui::EndChild();
            ImGui::PopStyleColor();

            ImGui::SameLine( 0.0f, 20.0f );
            if ( ImGui::GetContentRegionAvail().x < 350.0f )
            {
                ImGui::NewLine();
                ImGui::NewLine();
            }
        }
    }
}
