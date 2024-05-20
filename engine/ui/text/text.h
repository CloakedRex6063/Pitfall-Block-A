#pragma once

class Text : public UIElement
{
public:
    Text(Surface* screen, float2 newPos, const char* newText, int newTextColor, int2 newScale): UIElement(screen, newPos),
        text(newText), textColor(newTextColor), scale(newScale) {}
    void Render() override;
    [[nodiscard]] const char* GetText() const { return text; }
    void SetText(const char* newText) { text = newText; }

    void SetTextColor(int newTextColor) { textColor = newTextColor; }
    [[nodiscard]] int GetTextColor() const { return textColor; }
private:
    int2 scale = int2(0, 0);
    const char* text = {};
    int textColor;
};
