#pragma once

class UIElement;

class UIManager
{
public:
    UIManager(UIElement** newUIElements,int newNum) : uiElements(newUIElements), numElements(newNum) {}
    ~UIManager();
    void Tick() const;
    void Render() const;
    void MouseMove(int x, int y) {mousePos.x = x; mousePos.y = y;}

    UIElement* GetElement(int index) const {return uiElements[index];}

private:
    int2 mousePos = int2(0, 0);
    UIElement** uiElements = nullptr;
    int numElements = 0;
};
