#pragma once

#include "EnemyAIComponent.h"
#include "FiniteStateMachine.h"
#include "TankFieldControlComponent.h"


//STATES

//choose RondomDirection To Move tp
class IdleState : public AIState
{
public:
	IdleState(TankFieldControlComponent* field, dae::GameObject* tank, EnemyAIComponent * ai) :m_pField(field), m_pObj(tank),nm_pMe(ai){};
	~IdleState() override = default;

	void Update() override
	{
		auto p = glm::ivec2{};
		char possible = m_pField->GetPossibleDirectionToMove(m_pObj->GetTransform()->GetPosition(),p);

		int dir = rand() % 4 + 1;

		auto val = m_pField->GetCells();

		int id = nm_pMe->GetCurrentWaypointID();
		auto cell = val[id];
		switch (dir)
		{
		case 1:
			if (possible & DIRECTION_UP && 0 <= nm_pMe->GetNextWayPointID() - m_pField->GetWitdh() )
				nm_pMe->SetDirection(DIRECTION_UP);
			//val[nm_pMe->GetCurrentDirection()];
			nm_pMe->SetNextWayPointID(nm_pMe->GetNextWayPointID() - m_pField->GetWitdh());
			break;
		case 2:
			if (possible & DIRECTION_RIGHT && cell.y == val[id+1].y && val[id+1].Type == 0)
				nm_pMe->SetDirection(DIRECTION_RIGHT);
			nm_pMe->SetNextWayPointID(nm_pMe->GetNextWayPointID() - 1);
				break;
		case 3:
			if (possible & DIRECTION_DOWN && static_cast<int>(val.size()) >= nm_pMe->GetNextWayPointID() - m_pField->GetWitdh())
				nm_pMe->SetDirection(DIRECTION_DOWN);

			nm_pMe->SetNextWayPointID(nm_pMe->GetNextWayPointID() + m_pField->GetWitdh());
				break;
		case 4:
			if (possible & DIRECTION_LEFT && cell.y == val[id -1].y&& val[id - 1].Type == 0)
				nm_pMe->SetDirection(DIRECTION_LEFT);
			nm_pMe->SetNextWayPointID(nm_pMe->GetNextWayPointID() + 1);
				break;

		default:
			nm_pMe->SetDirection(DIRECTION_NONE);
			break;
		}

	}

private:

	EnemyAIComponent* nm_pMe;
	TankFieldControlComponent* m_pField;
	dae::GameObject* m_pObj;
};


class MoveState : public AIState
{
public:
	MoveState(Command* comm) : m_pCommand(comm) {};
	~MoveState() override 
	{
		delete m_pCommand;
	}

	void Update() override
	{
		m_pCommand->Execute();
	};
private:
	Command* m_pCommand = nullptr;
};


//CONDITIONS

class ArrivedAtInterSection final : public AIStateCondition
{
public:
	ArrivedAtInterSection(AIState* start, AIState* next,
		dae::GameObject* Obj, EnemyAIComponent* EnemyIControl,TankFieldControlComponent* field)
		:AIStateCondition(start, next), nm_pMe(EnemyIControl), m_pObj(Obj),nm_pField(field) {};

	void update() override
	{
		if(nm_pField)
		{
			//int id = nm_pMe->GetNextWayPointID();
			//if(id < 0 || nm_pField->GetWayPoints().size() < id -1)
			//	return;

			auto pos = m_pObj->GetTransform()->GetPosition();
			auto points = nm_pField->GetWayPoints();
			for (int i = 0; i < static_cast<int>(points.size()); ++i)
			{
			auto np = points[i];
			if (np.x - 3 <= pos.x && pos.x <= np.x + 3 && np.y - 3 <= pos.y &&  pos.y <= np.y + 3 &&
				nm_pMe->GetCurrentWaypointID() != i)
			{
				nm_pMe->SetCurrentWayPointID(i);
				m_Condition = true;
				return;
			}
				
			}

			 m_Condition = false;
		}
	//	auto& pos = m_pObj->GetTransform()->GetPosition();
	//	if (nm_pMe->GetFormerWayPoint().x + 2 >= pos.x &&
	//		nm_pMe->GetFormerWayPoint().y + 2 >= pos.y)
	//		m_Condition = true;
	//	else m_Condition = false;
	};

	bool IsConditionFufilled() override { return m_Condition; };
private:
	bool m_Condition = false;
	EnemyAIComponent* nm_pMe;
	TankFieldControlComponent* nm_pField= nullptr;
	dae::GameObject* m_pObj;


};

class GotANewDirection : public AIStateCondition
{
public:
	GotANewDirection(AIState* start,AIState* next,char dir, EnemyAIComponent* me)
	: AIStateCondition(start,next), nm_pMe(me),m_direction(dir) {}


	void update() override
	{
	};
	bool IsConditionFufilled() override { return nm_pMe->GetCurrentDirection() == m_direction; };
private:
	char m_direction = DIRECTION_NONE;
	EnemyAIComponent* nm_pMe;
};