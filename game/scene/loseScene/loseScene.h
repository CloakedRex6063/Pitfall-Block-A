#pragma once

class LoseScene final : public Scene
{
public:
    LoseScene(Surface* newScreen, Game* newGame);

    void Tick(float deltaTime) override;
    void Render() override;

    void Retry();
    void TitleScreen();
    void Quit();
};
