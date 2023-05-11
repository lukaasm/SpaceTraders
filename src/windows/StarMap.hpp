#pragma once

#include "imgui/widgets/imgui_canvas.h"

namespace lst
{
    class StarMap
    {
    public:
        void            DrawWindow();

        ImGuiEx::Canvas m_canvas;
    };
}