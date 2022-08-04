#pragma once
#include "MiniginPCH.h"
#include "TankGameScene.h"
#include "TronConstructor.h"
#include "WallComponent.h"

TankGameScene::TankGameScene(const std::string& name)
	:Scene(name)
{

}

void TankGameScene::Initialize()
{
	
	std::shared_ptr<dae::GameObject> playerTank = TronConstructor::PlayerTank();
	playerTank->GetTransform()->SetPosition(40, 40, 0);
	AddGameObject(playerTank);

	auto TestWall = std::make_shared<dae::GameObject>();

	SDL_Rect WallSize = SDL_Rect{10,10,-5,-5};
	auto wallComp = new WallComponent(WallSize);
	//wallComp->SetWallOffset();

	TestWall->AddComponent(wallComp);


	AddGameObject(TestWall);
}
