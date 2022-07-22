#include "MiniginPCH.h"
#include "ServiceLocator.h"

NullSoundSystem ServiceLocator::default_ss;
SoundSystem* ServiceLocator::ss_instance = &default_ss;