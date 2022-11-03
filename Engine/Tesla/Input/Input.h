#pragma once

namespace TESLA
{
    class Input
    {
    public:
        Input() = delete;
        static TESLA::Vector GetNormalizedCursorPos();
        static void Update();
    private:
        static TESLA::Vector mousePos;
    };
}
