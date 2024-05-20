#pragma once

class Scene
{
public:
    Scene(Surface* newScreen, Game* newGame) : screen(newScreen), game(newGame) {}
    virtual ~Scene() {delete uiManager;}
    virtual void Tick(float);
    virtual void Render();
    virtual void PhysicsTick();
    
    Surface* GetScreen() const {return screen;}
    Game* GetGame() const {return game;}
    UIManager* GetUIManager() const {return uiManager;}
    void MouseMove(int x, int y);

private:
    Surface* screen;
    Game* game;
    int2 mousePos = {0,0};
protected:
    UIManager* uiManager = nullptr;
};
