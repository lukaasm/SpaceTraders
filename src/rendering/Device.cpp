#include "Device.hpp"

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_win32.h"

#include <SDL.h>
#include <SDL_syswm.h>

namespace lst
{
    Device::~Device()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplSDL2_Shutdown();

        if ( m_pSwapChain )
        {
            m_pSwapChain->Release();
        }

        if ( m_pd3dDeviceContext )
        {
            m_pd3dDeviceContext->Release();
        }

        if ( m_pd3dDevice )
        {
            m_pd3dDevice->Release();
        }
    }

    bool Device::Initialize( SDL_Window * window )
    {
        SDL_SysWMinfo wmInfo;
        SDL_VERSION( &wmInfo.version );
        SDL_GetWindowWMInfo( window, &wmInfo );

        HWND hWnd = ( HWND )wmInfo.info.win.window;
        ::ImGui_ImplWin32_EnableAlphaCompositing( hWnd );

        // Setup swap chain
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory( &sd, sizeof( sd ) );
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT createDeviceFlags = 0;
        //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[ 2 ] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
        if ( ::D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice, &featureLevel, &m_pd3dDeviceContext ) != S_OK )
            return false;

        ResizeBackBuffer();

        ImGui_ImplSDL2_InitForD3D( window );
        ImGui_ImplDX11_Init( m_pd3dDevice, m_pd3dDeviceContext );

        return true;
    }

    void Device::ResizeBackBuffer()
    {
        if ( m_mainRenderTargetView )
        {
            m_mainRenderTargetView->Release();
            m_mainRenderTargetView = nullptr;
        }

        m_pSwapChain->ResizeBuffers( 0, 0, 0, DXGI_FORMAT_UNKNOWN, 0 );

        ID3D11Texture2D * pBackBuffer = nullptr;
        m_pSwapChain->GetBuffer( 0, IID_PPV_ARGS( &pBackBuffer ) );

        m_pd3dDevice->CreateRenderTargetView( pBackBuffer, nullptr, &m_mainRenderTargetView );
        pBackBuffer->Release();
    }

    void Device::BeginFrame()
    {
        ImGui_ImplSDL2_NewFrame();
        ImGui_ImplDX11_NewFrame();
    }

    void Device::EndFrame()
    {
        ImGui::Render();

        const float color[ 4 ] = { 0.0f, 0.0f, 0.0f, 1.0f };
        m_pd3dDeviceContext->OMSetRenderTargets( 1, &m_mainRenderTargetView, nullptr );
        m_pd3dDeviceContext->ClearRenderTargetView( m_mainRenderTargetView, color );

        ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData() );

        // Update and Render additional Platform Windows
        if ( ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        m_pSwapChain->Present( 1, 0 );
    }
}
