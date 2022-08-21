#pragma once
class AIState
{
public:
	AIState() = default;
	virtual ~AIState() = default;
	virtual void OnEnter(){};
	virtual void Update() = 0;
	virtual void OnExit(){};
private:

};

class AIStateCondition
{
public:
	virtual ~AIStateCondition() = default;

	AIStateCondition(AIState *current,AIState *next): m_CurrentState(current),m_NextState(next)
	{}
	virtual bool IsConditionFufilled() = 0;
	virtual void update() = 0;

	AIState* NextState() const { return m_NextState; };
	AIState* CurrentState() const { return m_CurrentState; };
private:
	AIState* m_CurrentState = nullptr;
	AIState* m_NextState = nullptr;

};

