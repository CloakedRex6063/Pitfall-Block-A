#include "precomp.h"
#include "text.h"

void Text::Render()
{
    GetScreen()->Print(text, static_cast<int>(pos.x), static_cast<int>(pos.y), textColor, scale);
}
