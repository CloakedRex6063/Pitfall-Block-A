#pragma once

// Using Jeremiah's Audio library

class SoundManager
{
    Audio::Sound** sounds;
    Audio::Sound** music;
    int numSounds;
    int numMusic;

    Game* game;
public:

    SoundManager(Game* game, Audio::Sound** newSounds, int newNumSounds, Audio::Sound** newMusic, int newNumMusic);

    ~SoundManager();

    void SetSound(int index, const char* path) const;
    void SetLoop(int index, bool bLoop) const;\
    float GetSoundVolume() const;
    void SetSoundVolume(float newVolume) const;
    void Play(int index) const;
    void Stop(int index) const;

    void PlayMusic(int index) const;
    void ReplayMusic(int index) const;
    void StopMusic(int index) const;
    float GetMusicVolume() const;
    void SetMusicVolume(float newVolume) const;
};
