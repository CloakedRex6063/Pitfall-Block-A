#pragma once

class WinScene final : public Scene   
{
public:
    WinScene(Surface* newScreen, Game* newGame);

    void Tick(float deltaTime) override;
    void Render() override;

    void TitleScreen();
    void Quit();
};
