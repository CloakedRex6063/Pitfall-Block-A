#pragma once

class UIElement
{
    Surface* screen = nullptr;

protected:
    Transform* transform = nullptr;
    float2 pos;

public:
    UIElement(Surface* screen, float2 newPos) : screen(screen), pos(newPos) {}

    virtual ~UIElement() {delete transform;}
    virtual void Tick() {}
    virtual void Render() = 0;
    virtual void OnHover() {}
    virtual void UnHover() {}
    virtual void OnPressed() {}
    virtual void OnReleased() {}
    virtual void OnHeld() {}

    Transform* GetTransform() const { return transform; }
    Surface* GetScreen() const { return screen; }

    bool bHovered = false;
};
