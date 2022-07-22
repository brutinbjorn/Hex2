//#pragma once
#include <list>
#include <map>
#include <mutex>
#include <thread>
#include <SDL_mixer.h>

struct SoundStats
{
	int m_id = -1;
	float m_volume = 1.f;
	std::string m_filename = "NONE";
};

class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	virtual void PlaySound(unsigned short id, float volume) = 0;
	virtual void PlaySoundEffect(unsigned short id, float volume) = 0;
	virtual void LoadSound(int id, const std::string& source) = 0;
	virtual void LoadSoundEffect(int id, const std::string& source) = 0;
};

class NullSoundSystem final : public SoundSystem
{
public:
	void PlaySound(unsigned short , float ) override {}
	void PlaySoundEffect(unsigned short , float ) override {};
	void LoadSound(int , const std::string& ) override {};
	void LoadSoundEffect(int , const std::string& ) override {};

};


#ifdef USE_SDLMIXER2
class SDLSoundSystem : public  SoundSystem
{
public:
	SDLSoundSystem();
	~SDLSoundSystem() override;

	void PlaySound(unsigned short id, float volume) override;
	void PlaySoundEffect(unsigned short id, float volume) override;
	void LoadSound(int id, const std::string& source) override;
	void LoadSoundEffect(int id, const std::string& source) override;

private:
	void Update();
	void I_playSound(int songId, float volume) ;
	void I_PlaySoundEffect(int effectId, float volume) ;
	//std::map<int, Mix_Chunk*> m_effects;

	//squeue

	std::list<SoundStats> m_SoundQueue;

	std::map<int, Mix_Music*> m_Songs;
	std::map<int, Mix_Chunk*> m_soundEffects;


	//thread
	std::atomic_bool m_isMuted = false;
	std::atomic_bool m_playNextSong = false;
	std::atomic_bool m_stopping = false;

	std::thread m_MusicUpdatejthread;
	std::mutex m_MutexSoundsQueueChanged;
	std::condition_variable m_WorkAvailable;
};
#endif

