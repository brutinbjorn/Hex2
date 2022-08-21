#include "EnemyAIComponent.h"

#include "TronAI.h"

void EnemyAIComponent::Initialize()
{
	auto wayPoints = nm_pField->GetWayPoints();
	float closestDistance = FLT_MAX;
	int closestPoints = -1; 
	for (int i = 0; i < wayPoints.size(); ++i)
	{
		auto pos = wayPoints[i];
		auto pPos = GetParent()->GetTransform()->GetPosition();

		float dist = pPos.x - pos.x + pPos.y - pos.y;
		if (dist < closestDistance)
			closestPoints = i;

	}
	m_currentWayPoint = closestPoints;
	m_NextWayPoint = closestPoints -1;
		
	

	auto Moveleft = new LimitedMoveCommandAlt(GetParent(), nm_pField, DIRECTION_LEFT, -1, 0,nm_pActor);
	auto leftState = new MoveState(Moveleft);
	m_Fsm.AddState(leftState);
	auto MoveRight = new LimitedMoveCommandAlt(GetParent(), nm_pField, DIRECTION_RIGHT, 1, 0, nm_pActor);
	auto rightState = new MoveState(MoveRight);
	m_Fsm.AddState(rightState);
	auto MoveUp = new LimitedMoveCommandAlt(GetParent(), nm_pField, DIRECTION_UP, 0, 1, nm_pActor);
	auto UpState = new MoveState(MoveUp);
	m_Fsm.AddState(UpState);
	auto MoveDown = new LimitedMoveCommandAlt(GetParent(), nm_pField, DIRECTION_DOWN, 0, -1, nm_pActor);
	auto DownState = new MoveState(MoveDown);
	m_Fsm.AddState(DownState);

	auto idle = new IdleState(nm_pField, GetParent(), this);
	m_Fsm.AddState(idle);
	m_Fsm.SetStartState(idle);

	auto GotUpDirection = new GotANewDirection(idle, UpState, DIRECTION_UP, this);
	m_Fsm.AddTransition(GotUpDirection);
	auto GotDownDirection = new GotANewDirection(idle, DownState, DIRECTION_DOWN, this);
	m_Fsm.AddTransition(GotDownDirection);
	auto GotRightDirection = new GotANewDirection(idle, rightState, DIRECTION_RIGHT, this);
	m_Fsm.AddTransition(GotRightDirection);
	auto GotLeftDirection = new GotANewDirection(idle, leftState, DIRECTION_LEFT, this);
	m_Fsm.AddTransition(GotLeftDirection);

	auto UpStop = new ArrivedAtInterSection(UpState, idle, GetParent(), this, nm_pField);
	m_Fsm.AddTransition(UpStop);
	auto downStop = new ArrivedAtInterSection(DownState, idle, GetParent(), this,nm_pField);
	m_Fsm.AddTransition(downStop);

	auto leftStop = new ArrivedAtInterSection(leftState, idle, GetParent(), this, nm_pField);
	m_Fsm.AddTransition(leftStop);
	auto RightStop = new ArrivedAtInterSection(rightState, idle, GetParent(), this, nm_pField);
	m_Fsm.AddTransition(RightStop);

}

void EnemyAIComponent::Update(const float dt)
{
	m_Fsm.Update(dt);
}
