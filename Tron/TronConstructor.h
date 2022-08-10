#pragma once
#include "GameObject.h"
#include "MiniginPCH.h"

namespace TronConstructor
{
	std::shared_ptr<dae::GameObject> PlayerTank();

	std::shared_ptr<dae::GameObject> TankGameField(const std::string& BackgroundImg, const std::string& PathJsonFile);



}

