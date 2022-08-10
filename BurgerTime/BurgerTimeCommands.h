#pragma once
#include "Command.h"
#include "GameObject.h"
#include "MoveGridComponent.h"


class MoveCommand : public Command
{
public:
	MoveCommand(ActorComponent* pActor,float XMove,float Ymove)
		:m_pActor(pActor),m_XMove(XMove),m_YMove(Ymove) {};
	~MoveCommand() override = default;
	void Execute() override
	{
		m_pActor->MoveTranslate(m_XMove, m_YMove);
	};
private:
	ActorComponent* m_pActor = nullptr;
	float m_XMove, m_YMove;
};

class LimitedMoveCommand : public Command
{
public:
	LimitedMoveCommand(dae::GameObject* actor, MoveGridComponent* grid, float xMove, float yMove)
		:m_pActor(actor), m_pGrid(grid), m_xMove(xMove), m_yMove(yMove){};
	~LimitedMoveCommand() override = default;

	void Execute() override
	{
		char val = m_pGrid->GetDirections(m_pActor->GetTransform()->GetPosition());
		if(val != 0)
		{
			
			auto actor = m_pActor->GetComponent<ActorComponent>();
			if ((DIRECTION_LEFT & val) && m_xMove < 0)
				actor->MoveTranslate(m_xMove, 0);
			if ((DIRECTION_RIGHT & val) && m_xMove > 0)
				actor->MoveTranslate(m_xMove, 0);
			if ((DIRECTION_UP & val) && m_yMove < 0)
				actor->MoveTranslate(0, m_yMove);
			if ((DIRECTION_DOWN & val) && m_yMove > 0)
				actor->MoveTranslate(0, m_yMove);
		}
	};

private:
	dae::GameObject* m_pActor = nullptr;
	MoveGridComponent* m_pGrid = nullptr;
	float m_xMove = 0.f;
	float m_yMove = 0.f;
};


class PrintCommand : public Command
{
public:
	PrintCommand() = default;
	~PrintCommand() override = default;

	void Execute() override
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		std::cout << "Mouse Pos:" << x << ":" << y << std::endl;

	}
private:

};

