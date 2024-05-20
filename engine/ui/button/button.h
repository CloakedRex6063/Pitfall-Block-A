#pragma once

template<typename F>
class Button : public UIElement
{
public:
    Button(Surface* screen, Sprite** newSprites, F* newObject, void (F::*newFunction)(), int2 newPos,
           const char* newText, int textColor, float2 offset, int2 scale) : UIElement(screen, newPos),
                                                 sprites(newSprites), function(newFunction),
                                                 object(newObject)
    {
        transform = new Transform(pos, int2(sprites[0]->GetWidth(), sprites[0]->GetHeight()));
        text = new Text(screen, float2(pos.x + offset.x, pos.y + offset.y), newText,
                        textColor, scale);
    }
    
    void Tick() override {}
    void Render() override
    {
        switch (curState)
        {
        case None:
            sprites[0]->Draw(GetScreen(), pos);
            break;
        case Hover:
            sprites[1]->Draw(GetScreen(), pos);
            break;
        case Pressed:
            sprites[2]->Draw(GetScreen(), pos);
            break;
        }
        text->Render();
    }
    void OnHeld() override
    {
        SetCurState(Pressed);
    }

    void OnReleased() override
    {
        (object->*function)();
    }

    void OnHover() override
    {
        SetCurState(Hover);
    }

    void UnHover() override
    {
        SetCurState(None);
    }

    enum State
    {
        None,
        Hover,
        Pressed
    };
    
    void SetCurState(State newState)
    {
        if (curState != newState)
        {
            curState = newState;
        }
    }

    Text* GetText() const { return text; }
    void SetText(Text* newText) { text = newText; }

private:
    Text* text;
    
    Sprite** sprites = nullptr;
    
    void(F::*function)() = nullptr;
    F* object = nullptr;

    State curState = None;
};
