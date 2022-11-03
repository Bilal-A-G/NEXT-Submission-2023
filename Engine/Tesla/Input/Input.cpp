#include "TSPch.h"
#include "Input.h"

#include "NextAPI/app.h"

TESLA::Vector TESLA::Input::mousePos;

TESLA::Vector TESLA::Input::GetNormalizedCursorPos()
{
    return TESLA::Vector((mousePos.x/APP_VIRTUAL_WIDTH - 1 + 0.5) * 2, (mousePos.y/APP_VIRTUAL_HEIGHT - 1 + 0.5) * 2, 0);
}

void TESLA::Input::Update()
{
    App::GetMousePos(mousePos.x, mousePos.y);
}


