#include "Application.hpp"

#include "api/Endpoint.hpp"

#include "imgui.h"
#include "imgui/Icons.hpp"

namespace lst
{
    void Application::DrawWindow()
    {
        lst::api::GetEndpoint().set_bearer_token_auth( "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZGVudGlmaWVyIjoiTE1YIiwiaWF0IjoxNjgzNzUwNDEyLCJzdWIiOiJhZ2VudC10b2tlbiJ9.WLJzLcF5KyKVJTnHzLYx507yKWWV-ceTgcYJHM8nOUnZ0NXA62h773I-3Tyg5hNlQFTCzrqYxlh7_J7qp09vzHZw8nOb01YKgznZodf62_MktfE_3O3R1FT355AWHlH7jVHZ2GE17xJSe8jqGRwT5HO-_8wVEW5NEEVkTMkQQz0mKH53SZ3Oczf3fmnb3FpA7LP2Ak2F1cq6ueqo7eRkR2cRa8Ewimyk5RbBhzUw2_hjyZTnHUAwPTsVwidJ3mIMavf84u6gYHUge0OaIAPrYXys_BF7OHhwcDbfGbAf4YltADp5iNtxGFXEpZpRWlxCYsrudbkkFaVs8h4fUi-OXFYJn8zyUixYO8DZDXRWaZ0u-avU55lxK7TgCktgOzZxLg5fLY0i6wt9pdz_bbzXKHhA8WSiL7okXBZfOga8vMWCibfg1C_NElYgEpfHuS80RkQC9GSIyHHR7XiR-j-Ugl6cqVA0666iNHNBs4DBSEqxZyIYeEUa7lPdh4O0PeTX" );

        if ( !ImGui::BeginTabBar( "##content" ) )
            return;

        if ( ImGui::BeginTabItem( ICON_FA_HOUSE" Star map##starmap" ) )
        {
            ImGui::BeginChild( "##starmap", ImGui::GetContentRegionAvail(), true );
            m_starmap.DrawWindow();
            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        if ( ImGui::BeginTabItem( ICON_FA_SHUTTLE_SPACE" Fleet##starship" ) )
        {
            ImGui::BeginChild( "##starmap", ImGui::GetContentRegionAvail(), true );
            m_fleet.DrawWindow();
            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        if ( ImGui::BeginTabItem( ICON_FA_FILE_CONTRACT" Contracts##contracts" ) )
        {
            ImGui::BeginChild( "##starmap", ImGui::GetContentRegionAvail(), true );
            m_contracts.DrawWindow();
            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}
