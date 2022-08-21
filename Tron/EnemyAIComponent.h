#pragma once
#include <BaseComponent.h>


#include "FiniteStateMachine.h"
#include "TankCommands.h"
//#include "FiniteStateMachine.h"
//#include "TronAI.h"


class EnemyAIComponent :
    public BaseComponent
{
public:
	EnemyAIComponent(TankFieldControlComponent* field,ActorComponent* aComp):nm_pField(field),nm_pActor(aComp)
	{} ;
	~EnemyAIComponent() override = default;
	EnemyAIComponent(const EnemyAIComponent& other) = delete;
	EnemyAIComponent(EnemyAIComponent&& other) noexcept = delete;
	EnemyAIComponent& operator=(const EnemyAIComponent& other) = delete;
	EnemyAIComponent& operator=(EnemyAIComponent&& other) noexcept = delete;

	void Initialize() override;
	void FixedUpdate(const float ) override {};
	void Update(const float dt) override;;
	void LateUpdate(const float ) override {};
	void Render() const override {};

	//glm::fvec2 GetFormerWayPoint() const { return m_lastWaypoint; };
	//glm::fvec2 GetNextWayPoint() const { return  m_NewWayPoint; };
	//void SetFormerWayPoint(glm::fvec2 point) { m_lastWaypoint = point; };
	//void SetNextWayPoint(glm::fvec2 point) { m_NewWayPoint = point; };

	void SetDirection(char direction) { m_Direction = direction; };
	char GetCurrentDirection() { return  m_Direction; }

	void SetCurrentWayPointID(int id) { m_currentWayPoint = id; }
	int GetCurrentWaypointID() { return  m_currentWayPoint; }

	void SetNextWayPointID(int id) { m_NextWayPoint = id; }
	int GetNextWayPointID() { return  m_NextWayPoint; }
private:
	TankFieldControlComponent* nm_pField;
	ActorComponent* nm_pActor;
	FSM m_Fsm;
	char m_Direction = DIRECTION_NONE;

	int m_currentWayPoint =0;
	int m_NextWayPoint = 0;

	//glm::fvec2 m_lastWaypoint;
	//glm::fvec2 m_NewWayPoint;


};

