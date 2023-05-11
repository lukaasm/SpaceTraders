#pragma once

#include "imgui.h"

namespace lst
{
    class Device;
}

namespace ImGui
{
    struct Context
    {
        Context();
        ~Context();

        void Initialize();
        bool PollEvents( lst::Device & device );
    };
}
