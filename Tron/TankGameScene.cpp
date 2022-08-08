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

//window
//1020,
//720,

void TankGameScene::Initialize()
{
	// BackGround
	std::shared_ptr<dae::GameObject> background = std::make_shared<dae::GameObject>();
	auto bgImage = new RenderComponent();
	bgImage->SetTexture("BackgroundTron.png");
	auto size = bgImage->GetTextureSize();
	bgImage->SetOffset(-(size.x / 2), -(size.y / 2));
	background->AddComponent(bgImage);
	background->SetPosition(510,360);
	AddGameObject(background);




	// Tank Logic
	std::shared_ptr<dae::GameObject> playerTank = TronConstructor::PlayerTank();
	playerTank->GetTransform()->SetPosition(40, 40, 0);
	AddGameObject(playerTank);



	// Tank Gun Input
	auto tankGun = playerTank->GetComponent<TankGunComponent>();

	dae::Action TurnGunLeft = dae::Action();
	TurnGunLeft.key = SDL_SCANCODE_Z;
	TurnGunLeft.pCommand = new TurnGunCommand(tankGun,-1);
	dae::InputManager::GetInstance().AddAction(TurnGunLeft);

	dae::Action TurnGunRight = dae::Action();
	TurnGunRight.key = SDL_SCANCODE_X;
	TurnGunRight.pCommand = new TurnGunCommand(tankGun, 1);
	dae::InputManager::GetInstance().AddAction(TurnGunRight);


	// Tank Body Input
	dae::Action MoveDown = dae::Action();
	MoveDown.key = SDL_SCANCODE_S;
	MoveDown.pCommand = new FreeMoveCommand(playerTank.get(),0,-1);
	dae::InputManager::GetInstance().AddAction(MoveDown);

	dae::Action MoveUp = dae::Action();
	MoveUp.key = SDL_SCANCODE_W;
	MoveUp.pCommand = new FreeMoveCommand(playerTank.get(), 0, 1);
	dae::InputManager::GetInstance().AddAction(MoveUp);

	dae::Action MoveLeft = dae::Action();
	MoveLeft.key = SDL_SCANCODE_A;
	MoveLeft.pCommand = new FreeMoveCommand(playerTank.get(), -1, 0);
	dae::InputManager::GetInstance().AddAction(MoveLeft);

	dae::Action MoveRight = dae::Action();
	MoveRight.key = SDL_SCANCODE_D;
	MoveRight.pCommand = new FreeMoveCommand(playerTank.get(), 1, 0);
	dae::InputManager::GetInstance().AddAction(MoveRight);




	//SDL_Rect WallSize = SDL_Rect{10,10,-5,-5};
	//auto wallComp = new WallComponent(WallSize);
	//wallComp->SetWallOffset();
	//TestWall->AddComponent(wallComp);


	//AddGameObject(TestWall);
}
