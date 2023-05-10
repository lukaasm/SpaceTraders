#pragma once

#include <d3d11.h>

struct SDL_Window;

namespace lst
{
    class Device
    {
    public:
        Device() = default;
        ~Device();

        bool                        Initialize( SDL_Window * window );

        void                        ResizeBackBuffer();

        void                        BeginFrame();
        void                        EndFrame();

        ID3D11Device *              m_pd3dDevice = nullptr;
        ID3D11DeviceContext *       m_pd3dDeviceContext = nullptr;
        IDXGISwapChain *            m_pSwapChain = nullptr;
        ID3D11RenderTargetView *    m_mainRenderTargetView = nullptr;
    };
}