#pragma once

#include "SoundSystem.h"


class ServiceLocator final
{
	static SoundSystem* ss_instance;
	static NullSoundSystem default_ss;
public:
	static SoundSystem& GetSoundSystem() { return *ss_instance; };

	static void RegisterSoundSystem(SoundSystem* ss)
	{
		ss_instance = ss == nullptr ? &default_ss : ss;
	}

	static void CleanUpSoundSystem()
	{
		delete ss_instance;
	}
};

