#pragma once
#include "MiniginPCH.h"
#include "TankGameScene.h"
#include "TronConstructor.h"

TankGameScene::TankGameScene(const std::string& name)
	:Scene(name)
{

}

void TankGameScene::Initialize()
{
	
	std::shared_ptr<dae::GameObject> playerTank = TronConstructor::PlayerTank();
	AddGameObject(playerTank);


}
