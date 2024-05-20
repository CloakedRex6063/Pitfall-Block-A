#include "precomp.h"
#include "optionsScene.h"

#include "engine/managers/soundManager.h"
#include "engine/ui/button/button.h"

OptionsScene::OptionsScene(Surface* newScreen, Game* newGame): Scene(newScreen, newGame)
{
    const auto elems = new UIElement*[7];
    const auto buttonSprites = new Sprite*[3];
    buttonSprites[0] = new Sprite(new Surface("assets/ui/buttonBlue.png"),1);
    buttonSprites[1] = new Sprite(new Surface("assets/ui/buttonBlueHover.png"),1);
    buttonSprites[2] = new Sprite(new Surface("assets/ui/buttonBluePressed.png"),1);
    elems[0] = new Button(GetScreen(), buttonSprites, this, &OptionsScene::UseCRT, int2(SCRWIDTH / 2 - 50,SCRHEIGHT / 2 - 100),
                          "Use CRT", GetGame()->settings.bUseCRT ? 0x00ff00 : 0xffffff, int2(50, 15), int2(2, 2));
    elems[1] = new Button(GetScreen(), buttonSprites, this, &OptionsScene::UseFXAA, int2(SCRWIDTH / 2 - 50,SCRHEIGHT / 2),
                      "Use FXAA", GetGame()->settings.bUseFXAA ? 0x00ff00 : 0xffffff, int2(50, 15), int2(2, 2));
    elems[2] = new Button(GetScreen(),buttonSprites,this,&OptionsScene::PlayMusic,int2(SCRWIDTH/2 - 50,SCRHEIGHT/2 + 100),
                          "Play Music",GetGame()->settings.musicVolume == 1.f ? 0x00ff00 : 0xffffff,int2(40,15),int2(2,2));
    elems[3] = new Button(GetScreen(),buttonSprites,this,&OptionsScene::PlaySFX,int2(SCRWIDTH/2 - 50,SCRHEIGHT/2 + 200),
                          " Play SFX",GetGame()->settings.soundVolume == 1.f ? 0x00ff00 : 0xffffff,int2(35,15),int2(2,2));
    elems[4] = new Button(GetScreen(),buttonSprites,this,&OptionsScene::GoBack,int2(0,SCRHEIGHT - 50),
                          "Go Back",0xffffff,int2(35,15),int2(2,2));
    elems[5] = new Text(GetScreen(),int2(SCRWIDTH/4 + 50,SCRHEIGHT/2 - 200),"CRT And FXAA require game restart",0xffffff, int2(3,3));
    elems[6] = new Text(GetScreen(),int2(SCRWIDTH/4 + 50,SCRHEIGHT/2 - 150),"All Settings are saved automatically",0xffffff, int2(3,3));
    uiManager = new UIManager(elems,7);
}

void OptionsScene::Tick(float deltaTime)
{
    Scene::Tick(deltaTime);
}

void OptionsScene::Render()
{
    Scene::Render();
}

void OptionsScene::UseCRT()
{
    GetGame()->settings.bUseCRT = !GetGame()->settings.bUseCRT;
    const auto button = dynamic_cast<Button<OptionsScene>*>(GetUIManager()->GetElement(0));
    button->GetText()->SetTextColor(GetGame()->settings.bUseCRT ? 0x00ff00 : 0xffffff);
}

void OptionsScene::UseFXAA()
{
    GetGame()->settings.bUseFXAA = !GetGame()->settings.bUseFXAA;
    const auto button = dynamic_cast<Button<OptionsScene>*>(GetUIManager()->GetElement(1));
    button->GetText()->SetTextColor(GetGame()->settings.bUseFXAA ? 0x00ff00 : 0xffffff);
}

void OptionsScene::PlayMusic()
{
    const auto button = dynamic_cast<Button<OptionsScene>*>(GetUIManager()->GetElement(2));
    if (GetGame()->GetSoundManager()->GetMusicVolume() == 0.f)
    {
        GetGame()->GetSoundManager()->SetMusicVolume(1.f);
        GetGame()->GetSoundManager()->ReplayMusic(0);
        button->GetText()->SetTextColor(0x00ff00);
    }
    else
    {
        GetGame()->GetSoundManager()->SetMusicVolume(0.f);
        button->GetText()->SetTextColor(0xffffff);
    }
}

void OptionsScene::PlaySFX()
{
    const auto button = dynamic_cast<Button<OptionsScene>*>(GetUIManager()->GetElement(3));
    if (GetGame()->GetSoundManager()->GetSoundVolume() == 0.f)
    {
        GetGame()->GetSoundManager()->SetSoundVolume(1.f);
        GetGame()->GetSoundManager()->Play(0);
        button->GetText()->SetTextColor(0x00ff00);
    }
    else
    {
        GetGame()->GetSoundManager()->SetSoundVolume(0.f);
        button->GetText()->SetTextColor(0xffffff);
    }
}

void OptionsScene::GoBack()
{
    GetGame()->SetGameState(Scene_MainMenu);
}
