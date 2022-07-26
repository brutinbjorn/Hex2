
#include "TankGameScene.h"
#include "MiniginPCH.h"
#include "TronConstructor.h"

void TankGameScene::Initialize()
{
	
	std::shared_ptr<dae::GameObject> playerTank = ObjectConstructor::PlayerTank();

	AddGameObject(playerTank);


}
