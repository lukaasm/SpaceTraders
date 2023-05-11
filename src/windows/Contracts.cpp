#include "Contracts.hpp"

#include "api/Contract.hpp"

#include "imgui.h"
#include "imgui/Icons.hpp"

#include <format>

namespace lst
{
    void Contracts::DrawWindow()
    {
        static auto s_contracts = api::GetMyContracts();
        if ( !s_contracts.has_value() )
            return ImGui::TextDisabled( "Failed to acquired contracts list!" );

        if ( !ImGui::BeginTable( "##contracts", 11, ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersInner, ImGui::GetContentRegionAvail() ) )
            return;

        ImGui::TableSetupColumn( "Status" );
        ImGui::TableSetupColumn( "Faction" );
        ImGui::TableSetupColumn( "Type" );
        ImGui::TableSetupColumn( "Deadline" );
        ImGui::TableSetupColumn( "Payment" );
        ImGui::TableSetupColumn( "Trade" );
        ImGui::TableSetupColumn( "Destination" );
        ImGui::TableSetupColumn( "Expiration" );

        ImGui::TableHeadersRow();

        ImGui::Indent();
        for ( auto & contract : s_contracts.value() )
        {
            ImGui::TableNextRow();
            if ( ImGui::TableSetColumnIndex( 0 ) )
            {
                ImGui::AlignTextToFramePadding();
                if ( contract.fulfilled )
                {
                    ImGui::PushStyleColor( ImGuiCol_Text, ImVec4{ 0.0f,0.5f,0.0f,1.0f } );
                    ImGui::AlignTextToFramePadding();
                    ImGui::Text( ICON_FA_CIRCLE_CHECK );
                    ImGui::PopStyleColor();
                }
                else if ( contract.accepted )
                {
                    ImGui::PushStyleColor( ImGuiCol_Text, ImVec4{ 0.5f,0.5f,0.0f,1.0f } );
                    ImGui::AlignTextToFramePadding();
                    ImGui::Text( ICON_FA_GROUP_ARROWS_ROTATE );
                    ImGui::PopStyleColor();
                }
                else
                {
                    ImGui::PushStyleColor( ImGuiCol_Button, ImVec4{ 0.0f,0.5f,0.0f,1.0f } );
                    if ( ImGui::Button( ICON_FA_SQUARE_PLUS" Accept##accept", { -FLT_MIN, 0.0f } ) )
                    {
                    }
                    ImGui::PopStyleColor();
                }
            }

            if ( ImGui::TableSetColumnIndex( 1 ) )
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text( contract.factionSymbol.c_str() );
            }

            if ( ImGui::TableSetColumnIndex( 2 ) )
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text( contract.type.c_str() );
            }

            if ( ImGui::TableSetColumnIndex( 3 ) )
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text( contract.terms.deadline.c_str() );
            }

            if ( ImGui::TableSetColumnIndex( 4 ) )
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text( std::format( ICON_FA_DOLLAR_SIGN"{} + " ICON_FA_DOLLAR_SIGN"{}", contract.terms.payment.onAccepted, contract.terms.payment.onFulfilled ).c_str() );
            }

            if ( ImGui::TableSetColumnIndex( 7 ) )
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text( contract.expiration.c_str() );
            }
        }
        ImGui::Unindent();

        ImGui::EndTable();
    }
}
