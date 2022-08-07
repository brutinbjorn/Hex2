#pragma once
#include "MiniginPCH.h"
#include "TankGameScene.h"
#include "TronConstructor.h"
#include "WallComponent.h"
#include "InputManager.h"
#include "TankCommands.h"

TankGameScene::TankGameScene(const std::string& name)
	:Scene(name)
{

}

void TankGameScene::Initialize()
{
	std::shared_ptr<dae::GameObject> playerTank = TronConstructor::PlayerTank();
	playerTank->GetTransform()->SetPosition(40, 40, 0);
	AddGameObject(playerTank);

	// Tank Gun
	auto tankGun = playerTank->GetComponent<TankGunComponent>();

	dae::Action TurnGunLeft = dae::Action();
	TurnGunLeft.key = SDL_SCANCODE_Z;
	TurnGunLeft.pCommand = new TurnGunCommand(tankGun,-1);
	dae::InputManager::GetInstance().AddAction(TurnGunLeft);

	dae::Action TurnGunRight = dae::Action();
	TurnGunRight.key = SDL_SCANCODE_X;
	TurnGunRight.pCommand = new TurnGunCommand(tankGun, 1);
	dae::InputManager::GetInstance().AddAction(TurnGunRight);




	//auto TestWall = std::make_shared<dae::GameObject>();




	//SDL_Rect WallSize = SDL_Rect{10,10,-5,-5};
	//auto wallComp = new WallComponent(WallSize);
	//wallComp->SetWallOffset();
	//TestWall->AddComponent(wallComp);


	//AddGameObject(TestWall);
}
