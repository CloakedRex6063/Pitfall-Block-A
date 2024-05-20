#include "precomp.h"
#include "soundManager.h"

SoundManager::SoundManager(Game* game, Audio::Sound** newSounds, int newNumSounds, Audio::Sound** newMusic,
    int newNumMusic):
    sounds(newSounds), music(newMusic), numSounds(newNumSounds), numMusic(newNumMusic), game(game)
{
    for (auto i = 0; i < numSounds; i++)
    {
        sounds[i]->setVolume(game->settings.soundVolume);
    }
    for (auto i = 0; i < numMusic; i++)
    {
        music[i]->setVolume(game->settings.musicVolume);
    }
}

SoundManager::~SoundManager()
{
    for (auto i = 0; i < numSounds; i++)
    {
        if (sounds[i])
        {
            delete sounds[i];
        }
    }

    for (auto i = 0; i < numMusic; i++)
    {
        if (music[i])
        {
            delete music[i];
        }
    }
    
    delete[] sounds;
    delete[] music;
}

void SoundManager::SetSound(int index, const char* path) const
{
    if (sounds[index])
    {
        sounds[index] = new Audio::Sound(path);
    }
}

void SoundManager::SetLoop(int index, bool bLoop) const
{
    sounds[index]->setLooping(bLoop);
}

float SoundManager::GetSoundVolume() const
{
    return game->settings.soundVolume;
}

void SoundManager::SetSoundVolume(float newVolume) const
{
    game->settings.soundVolume = newVolume;
    for (auto i = 0; i < numSounds; i++)
    {
        sounds[i]->setVolume(game->settings.soundVolume);
    }
}

void SoundManager::Play(int index) const
{
    sounds[index]->play();
}

void SoundManager::Stop(int index) const
{
    sounds[index]->stop();
}

void SoundManager::PlayMusic(int index) const
{
    music[index]->setVolume(game->settings.musicVolume);
    music[index]->play();
}

void SoundManager::ReplayMusic(int index) const
{
    music[index]->replay();
}

void SoundManager::StopMusic(int index) const
{
    music[index]->stop();
}

float SoundManager::GetMusicVolume() const
{
    return game->settings.musicVolume;
}

void SoundManager::SetMusicVolume(float newVolume) const
{
    game->settings.musicVolume = newVolume;
    for (auto i = 0; i < numMusic; i++)
    {
        music[i]->setVolume(game->settings.musicVolume);
    }
}
