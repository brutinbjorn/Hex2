#pragma once
#include "MiniginPCH.h"
#include "TankGameScene.h"

#include "EnemyTankComponent.h"
#include "HealthComponent.h"
#include "TronConstructor.h"
#include "WallComponent.h"
#include "InputManager.h"
#include "TankCommands.h"
#include "TankFieldControlComponent.h"

#include "ObjectConstructor.h"
#include "ScoreComponent.h"
#include "TankControlComponent.h"

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

	//std::shared_ptr<dae::GameObject> Field = TronConstructor::TankGameField("BackgroundTron.png", "TronFieldPathWalls.json");
	//AddGameObject(Field);


	std::shared_ptr<dae::GameObject> Field = TronConstructor::TankGameFieldAlt("", "TronFieldAlt1.json",{32,32});
	AddGameObject(Field);

	auto fieldControl = Field->GetComponent<TankFieldControlComponent>();

	auto TankStartPos = fieldControl->GetPlayerStartingPosition();
	auto EnemyStartPos = fieldControl->GetEnemyStartPosition();


	// Tank Logic
	std::shared_ptr<dae::GameObject> playerTank = TronConstructor::PlayerTank();
	playerTank->GetTransform()->SetPosition(static_cast<float>(TankStartPos.x),static_cast<float>(TankStartPos.y), 0);
	AddGameObject(playerTank);

	auto enemyTank = TronConstructor::EnemyTank(fieldControl);
	enemyTank->GetTransform()->SetPosition(static_cast<float>(EnemyStartPos.x),static_cast<float>(EnemyStartPos.y),0);
	AddGameObject(enemyTank);


	auto score = ObjectConstructor::ScoreBar("Lingua.otf", "Score: ", 20, {100,30});
	AddGameObject(score);
	auto scoreComp = score->GetComponent<ScoreComponent>();
	enemyTank->GetComponent<EnemyTankComponent>()->GetSubject()->AddObserver(scoreComp);

	auto LiveBar = ObjectConstructor::HealthBar({ 100,60,0 },"HeartSymbol.png");

	auto lives = LiveBar->GetComponent<HealthComponent>();
	playerTank->GetComponent<TankControlComponent>()->GetSubject()->AddObserver(lives);
	AddGameObject(LiveBar);



	// Tank Gun Input
	auto tankGun = playerTank->GetComponent<TankGunComponent>();

	dae::Action TurnGunLeft = dae::Action();
	TurnGunLeft.key = SDL_SCANCODE_Z;
	TurnGunLeft.pCommand = new TurnGunCommand(tankGun,-3);
	dae::InputManager::GetInstance().AddAction(TurnGunLeft);

	dae::Action TurnGunRight = dae::Action();
	TurnGunRight.key = SDL_SCANCODE_X;
	TurnGunRight.pCommand = new TurnGunCommand(tankGun, 3);
	dae::InputManager::GetInstance().AddAction(TurnGunRight);

	dae::Action FireGun = dae::Action();
	FireGun.key = SDL_SCANCODE_C;
	FireGun.pCommand = new FireGunCommand(tankGun);
	dae::InputManager::GetInstance().AddAction(FireGun);


	auto ac = playerTank->GetComponent<ActorComponent>();
	//movement
	dae::Action MoveDownLocked = dae::Action();
	MoveDownLocked.key = SDL_SCANCODE_DOWN;
	MoveDownLocked.pCommand = new LimitedMoveCommandAlt(playerTank.get(), fieldControl,DIRECTION_DOWN, 0, 1,ac);
	dae::InputManager::GetInstance().AddAction(MoveDownLocked);

	dae::Action MoveUpLocked = dae::Action();
	MoveUpLocked.key = SDL_SCANCODE_UP;
	MoveUpLocked.pCommand = new LimitedMoveCommandAlt(playerTank.get(), fieldControl,DIRECTION_UP, 0, -1,ac);
	dae::InputManager::GetInstance().AddAction(MoveUpLocked);

	dae::Action MoveLeftLocked = dae::Action();
	MoveLeftLocked.key = SDL_SCANCODE_LEFT;
	MoveLeftLocked.pCommand = new LimitedMoveCommandAlt(playerTank.get(), fieldControl,DIRECTION_LEFT, -1, 0,ac);
	dae::InputManager::GetInstance().AddAction(MoveLeftLocked);

	dae::Action MoveRightLocked = dae::Action();
	MoveRightLocked.key = SDL_SCANCODE_RIGHT;
	MoveRightLocked.pCommand = new LimitedMoveCommandAlt(playerTank.get(), fieldControl,DIRECTION_RIGHT, 1, 0,ac);
	dae::InputManager::GetInstance().AddAction(MoveRightLocked);



#pragma region old
	//// Tank Body Input
	//dae::Action MoveDownLocked = dae::Action();
	//MoveDownLocked.key = SDL_SCANCODE_DOWN;
	//MoveDownLocked.pCommand = new LimitedMoveCommand(playerTank.get(), fieldControl,0, 1);
	//dae::InputManager::GetInstance().AddAction(MoveDownLocked);

	//dae::Action MoveUpLocked = dae::Action();
	//MoveUpLocked.key = SDL_SCANCODE_UP;
	//MoveUpLocked.pCommand = new LimitedMoveCommand(playerTank.get(), fieldControl, 0, -1);
	//dae::InputManager::GetInstance().AddAction(MoveUpLocked);

	//dae::Action MoveLeftLocked = dae::Action();
	//MoveLeftLocked.key = SDL_SCANCODE_LEFT;
	//MoveLeftLocked.pCommand = new LimitedMoveCommand(playerTank.get(), fieldControl, -1, 0);
	//dae::InputManager::GetInstance().AddAction(MoveLeftLocked);

	//dae::Action MoveRightLocked = dae::Action();
	//MoveRightLocked.key = SDL_SCANCODE_RIGHT;
	//MoveRightLocked.pCommand = new LimitedMoveCommand(playerTank.get(), fieldControl, 1, 0);
	//dae::InputManager::GetInstance().AddAction(MoveRightLocked);

#pragma endregion old

#ifdef _DEBUG
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
#endif




	//SDL_Rect WallSize = SDL_Rect{10,10,-5,-5};
	//auto wallComp = new WallComponent(WallSize);
	//wallComp->SetWallOffset();
	//TestWall->AddComponent(wallComp);


	//AddGameObject(TestWall);
}
