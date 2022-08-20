#pragma once
#include "Command.h"
#include "ENUMS.h"
#include "GameObject.h"
#include "TankFieldControlComponent.h"
#include "TankGunComponent.h"
#include "TankFieldLineComponent.h"


class LimitedMoveCommand : public Command
{
public:
	LimitedMoveCommand(dae::GameObject* actor, TankFieldControlComponent* grid, float xMove, float yMove)
		:m_pActor(actor), m_pGrid(grid), m_xMove(xMove), m_yMove(yMove) {};
	~LimitedMoveCommand() override = default;

	void Execute() override
	{
		glm::ivec2 centerPos;

		/*
		 *  RECONS: inverse the request?
		 *	instead of asking all the lines where the player can move to, instead ask IF he can move in the REQUESTED DIRECTION.
		 */

		char val = m_pGrid->GetPossibleDirectionToMove(m_pActor->GetTransform()->GetPosition(),centerPos);
		if (val != 0)
		{
			auto actor = m_pActor->GetTransform();
			if ((DIRECTION_LEFT & val) && m_xMove < 0)
				actor->Translate(m_xMove, 0,0);
			if ((DIRECTION_RIGHT & val) && m_xMove > 0)
				actor->Translate(m_xMove, 0,0);
			if ((DIRECTION_UP & val) && m_yMove < 0)
				actor->Translate(0, m_yMove,0);
			if ((DIRECTION_DOWN & val) && m_yMove > 0)
				actor->Translate(0, m_yMove,0);
		}
	};

private:
	dae::GameObject* m_pActor = nullptr;
	TankFieldControlComponent* m_pGrid = nullptr;
	float m_xMove = 0.f;
	float m_yMove = 0.f;
};
class LimitedMoveCommandAlt : public Command
{
public:
	LimitedMoveCommandAlt(dae::GameObject* actor, TankFieldControlComponent* grid, char Direction, float x, float y) :
		m_pActor(actor),m_pGrid(grid),
		m_direction(Direction), m_xMove(x), m_yMove(y) {};
	~LimitedMoveCommandAlt() override = default;

	void Execute() override
	{
		glm::ivec2 centerPos;
		if (m_pGrid->AskIfPlayerCanMoveInRequestedDirection(m_direction, m_pActor->GetTransform()->GetPosition(), centerPos))
		{
			m_pActor->GetTransform()->Translate(m_xMove, m_yMove, 0);

			auto pos = m_pActor->GetTransform()->GetPosition();
			if(m_direction == DIRECTION_LEFT || m_direction == DIRECTION_RIGHT)
			{
				m_pActor->GetTransform()->SetPosition(pos.x, static_cast<float>(centerPos.y), 0);
			}

			if (m_direction == DIRECTION_UP || m_direction == DIRECTION_DOWN)
			{
				m_pActor->GetTransform()->SetPosition(static_cast<float>(centerPos.x), pos.y, 0);
			}
		}

	};
private:
	char m_direction = 0;
	float m_xMove = 0;
	float m_yMove = 0;

	TankFieldControlComponent* m_pGrid = nullptr;
	dae::GameObject* m_pActor = nullptr;

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