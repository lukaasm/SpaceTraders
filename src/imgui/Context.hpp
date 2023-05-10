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

        bool PollEvents( lst::Device & device );
    };
}
