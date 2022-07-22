#include "MiniginPCH.h"
#include "SoundSystem.h"

#include <thread>


SDLSoundSystem::SDLSoundSystem()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error" << Mix_GetError << std::endl;
	else
		std::cout << "SDL mix started" << std::endl;

	m_MusicUpdatejthread = std::thread([this] {this->Update(); });
}

SDLSoundSystem::~SDLSoundSystem()
{

	m_SoundQueue.clear();

	std::cout << "request stop \n" << std::endl;
	m_stopping = true;
	m_WorkAvailable.notify_one();

	//if(!m_MusicUpdatejthread.request_stop())
	//	std::cout << "Cant Stop Wont Stop \n";
	
	m_MusicUpdatejthread.join();

	for (std::map<int, Mix_Music*>::iterator songIter = m_Songs.begin(); songIter != m_Songs.end(); songIter++)
	{
		Mix_FreeMusic(songIter->second);
	}

	for (std::map<int, Mix_Chunk*>::iterator effectIter = m_soundEffects.begin(); effectIter != m_soundEffects.end(); effectIter++)
	{
		Mix_FreeChunk(effectIter->second);
	}

	Mix_CloseAudio();
	Mix_Quit();

}

void SDLSoundSystem::PlaySound(unsigned short id, float volume)
{
	float clampedVol = std::clamp(volume, 0.f, 1.f);

	SoundStats newSound{ id,clampedVol,"No Name" };
	std::lock_guard mLock{ m_MutexSoundsQueueChanged }; // lock when accessing soundQueue
	m_SoundQueue.push_back(newSound);

	m_WorkAvailable.notify_one();
}

void SDLSoundSystem::PlaySoundEffect(unsigned short id, float volume)
{
	//RECONS no list to add soundeffects ???
	float clampedVol = std::clamp(volume, 0.f, 1.f);

	I_PlaySoundEffect(id, (clampedVol));
}

void SDLSoundSystem::LoadSound(int id, const std::string& source)
{
	std::string fullpath = "../Data/sounds/";
	fullpath.append(source);

	
	Mix_Music* music = Mix_LoadMUS( fullpath.c_str());
	if (music != nullptr)
	{
		m_Songs[id] = music;
		std::cout << "music loaded at: " << id << std::endl;
	}
	else
		std::cout << "no music found at: " << fullpath << " error: " << Mix_GetError << std::endl;
	//if()
	//music = Mix_LoadMUS("../Data/sounds/piano2.wav");
	//if(music != nullptr)
	//{
	//	m_Songs[id] = music;
	//	std::cout << "music loaded at: " << id << std::endl;
	//}
	//else
	//	std::cout << "no music found at: " << fullpath << " error: " << Mix_GetError << std::endl;
}

void SDLSoundSystem::LoadSoundEffect(int id, const std::string& source)
{
	std::string fullpath = "../Data/";
	fullpath.append(source);

	Mix_Chunk* effect = Mix_LoadWAV(source.c_str());
	if (effect != nullptr)
	{
		m_soundEffects[id] = effect;
		std::cout << "effect loaded at: " << id << std::endl;
	}
	else
		std::cout << "no effect found at: " << fullpath << " error: " << Mix_GetError << std::endl;
}

void SDLSoundSystem::Update()
{
	do // keep running until stop is triggered
	{
		bool HasAudio = false;
		SoundStats soundToPlay;
		std::unique_lock mlock{ m_MutexSoundsQueueChanged }; // lock when accessing SoundQueue
		if (!m_SoundQueue.empty() && 0 == Mix_PlayingMusic())
		{
			soundToPlay = m_SoundQueue.front();
			m_SoundQueue.pop_front();
			HasAudio = true;
		}
		mlock.unlock();

		if (HasAudio) // check if there are songs to play AND is the current music not playing?
		{
			if (!m_isMuted)
			{
				I_playSound(soundToPlay.m_id, soundToPlay.m_volume);
			}
		}
		mlock.lock();
		if (m_SoundQueue.empty()) // if sound Queue is empty wait until you get message to do stuff
			m_WorkAvailable.wait(mlock);
		else
		{
			mlock.unlock();
		}
		

	} while (!m_stopping);

	std::cout << "update sound ended" << std::endl;
}

//internal
void SDLSoundSystem::I_playSound(int songId, float volume) 
{
	int ConvertedVolume = static_cast<int>(std::clamp(volume, 0.f, 1.f) * MIX_MAX_VOLUME);

	int channel = Mix_PlayMusic(m_Songs[songId], 1);
	if (channel == -1)
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
	Mix_Volume(channel, ConvertedVolume);
	std::cout << "playing music id: " << songId << "  on channel " << channel << std::endl;

}

//internal
void SDLSoundSystem::I_PlaySoundEffect(int effectId, float volume) 
{
	int ConvertedVolume = static_cast<int>(std::clamp(volume, 0.f, 1.f) * MIX_MAX_VOLUME );

	Mix_VolumeChunk(m_soundEffects[effectId], ConvertedVolume );
	Mix_PlayChannel(-1, m_soundEffects[effectId], 0);
}


