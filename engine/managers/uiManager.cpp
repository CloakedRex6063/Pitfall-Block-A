#include "precomp.h"
#include "uiManager.h"

UIManager::~UIManager()
{
    for(auto i = 0; i < numElements; i++)
    {
        delete uiElements[i];
    }
    delete[] uiElements;
}

void UIManager::Tick() const
{
    for(auto i = 0; i < numElements; i++)
    {
        uiElements[i]->Tick();

        if (uiElements[i]->GetTransform())
        {
            const auto elemTopLeft = uiElements[i]->GetTransform()->GetScreenLoc();
            const auto elemBotRight = elemTopLeft + uiElements[i]->GetTransform()->GetDim();
        
            if (static_cast<float>(mousePos.x) >= elemTopLeft.x && static_cast<float>(mousePos.x) <= elemBotRight.x &&
                static_cast<float>(mousePos.y) >= elemTopLeft.y && static_cast<float>(mousePos.y) <= elemBotRight.y)
            {
                if (Input::IsKeyReleased(VK_LBUTTON))
                {
                    uiElements[i]->OnReleased();
                    return;
                }
                if (Input::IsKeyHeld(VK_LBUTTON))
                {
                    uiElements[i]->OnHeld();
                    return;
                }
                uiElements[i]->bHovered = true;
                uiElements[i]->OnHover();
                return;
            }
            if (uiElements[i]->bHovered)
            {
                uiElements[i]->bHovered = false;
                uiElements[i]->UnHover();
            }
        }
    }
}

void UIManager::Render() const
{
    for(auto i = 0; i < numElements; i++)
    {
        uiElements[i]->Render();
    }
}
