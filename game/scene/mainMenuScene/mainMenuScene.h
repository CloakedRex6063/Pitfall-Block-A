#pragma once

class MainMenuScene final : public Scene
{
public:
    MainMenuScene(Surface* newScreen, Game* newGame);

    void Tick(float deltaTime) override;
    void Render() override;
    void PhysicsTick() override;

    void Play();
    void Resume();
    void Options();
    void Quit();
};
