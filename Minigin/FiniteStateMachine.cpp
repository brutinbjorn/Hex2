#include "MiniginPCH.h"
#include "FiniteStateMachine.h"

bool FSM::AddState(AIState* toAdd)
{
	auto val = std::find(m_States.begin(), m_States.end(), toAdd);
	if (val == m_States.end())
	{
		m_States.push_back(toAdd);
		return true;
	}
	return false;
}

bool FSM::AddTransition(AIStateCondition* toAdd)
{
	auto val = std::find(m_conditions.begin(), m_conditions.end(), toAdd);
	if (val == m_conditions.end())
	{
		m_conditions.push_back(toAdd);
		return true;
	}
	return false;
}

void FSM::SetStartState(AIState* toSetAdd)
{
	auto val = std::find(m_States.begin(), m_States.end(), toSetAdd);
	if(val == m_States.end())
	{
		m_States.push_back(toSetAdd);
	}
	m_ActiveState = toSetAdd;
}
