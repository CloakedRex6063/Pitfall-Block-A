#pragma once

class OptionsScene : public Scene
{
public:
    OptionsScene(Surface* newScreen, Game* newGame);

    void Tick(float deltaTime) override;
    void Render() override;

    void UseCRT();
    void UseFXAA();
    void PlayMusic();
    void PlaySFX();
    void GoBack();
};
