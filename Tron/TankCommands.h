#pragma once
#include "Command.h"
#include "GameObject.h"
#include "TankFieldGridComponent.h"
#include "TankGunComponent.h"

//enum Directions
//{
//	right = 0b0001,
//	left = 0b0010,
//	up = 0b0100,
//	down = 0b1000
//};

class LimitedMoveCommand : public Command
{
public:
	LimitedMoveCommand(dae::GameObject* actor, TankFieldGridComponent* grid, float xMove, float yMove)
		:m_pActor(actor), m_pGrid(grid), m_xMove(xMove), m_yMove(yMove) {};
	~LimitedMoveCommand() override = default;

	void Execute() override
	{
		char val = m_pGrid->GetDirections(m_pActor->GetTransform()->GetPosition());
		if (val != 0)
		{

			auto actor = m_pActor->GetComponent<ActorComponent>();
			if ((left & val) && m_xMove < 0)
				actor->MoveTranslate(m_xMove, 0);
			if ((right & val) && m_xMove > 0)
				actor->MoveTranslate(m_xMove, 0);
			if ((up & val) && m_yMove < 0)
				actor->MoveTranslate(0, m_yMove);
			if ((down & val) && m_yMove > 0)
				actor->MoveTranslate(0, m_yMove);
		}
	};

private:
	dae::GameObject* m_pActor = nullptr;
	TankFieldGridComponent* m_pGrid = nullptr;
	float m_xMove = 0.f;
	float m_yMove = 0.f;
};

class FreeMoveCommand : public Command
{
public:
	FreeMoveCommand(dae::GameObject* actor, float xMove, float yMove)
		:m_pActor(actor), m_xMove(xMove), m_yMove(yMove) {};
	void Execute() override
	{
		m_pActor->GetTransform()->Translate(m_xMove, m_yMove, 0);
	};
private:
	dae::GameObject* m_pActor;
	float m_xMove = 0.f;
	float m_yMove = 0.f;
};

class TurnGunCommand : public Command
{
public:
	TurnGunCommand(TankGunComponent* GunComp,float direction) :m_pGunComp(GunComp),m_dir(direction) { };
	void Execute() override
	{
		m_pGunComp->RotateGun(m_dir);
	};

private:
	TankGunComponent* m_pGunComp = nullptr;
	float m_dir;
};

class FireGunCommand : public Command
{
public:
	FireGunCommand(TankGunComponent* gunComp) :m_pGunComp(gunComp) {};
	void Execute() override
	{
		m_pGunComp->ShootGun();
	}
private:
	TankGunComponent* m_pGunComp = nullptr;
};