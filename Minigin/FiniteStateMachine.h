#pragma once

#include "AIStates.h"
#include "vector"
class FSM
{
public:
	FSM() = default;
	~FSM()
	{
		for (size_t i = 0; i < m_States.size(); ++i)
		{
			delete m_States[i];
		}

		for (size_t i = 0; i < m_conditions.size(); ++i)
		{
			delete m_conditions[i];
		}

	};
	FSM(const FSM& other) = delete;
	FSM(FSM&& other) noexcept = delete;
	FSM& operator=(const FSM& other) = delete;
	FSM& operator=(FSM&& other) noexcept = delete;

	void Update(const float)
	{
		m_ActiveState->Update();

		for (size_t i = 0; i < m_conditions.size(); ++i)
		{
			if(m_ActiveState == m_conditions[i]->CurrentState())
			{
				
				m_conditions[i]->update();
				if (m_conditions[i]->IsConditionFufilled())
				{
					m_ActiveState->OnExit();
					m_ActiveState = m_conditions[i]->NextState();
					m_ActiveState->OnEnter();
					break;
				}
			}
		}


	}

	//returns false if already in list;
	bool AddState(AIState* toAdd);;
	bool AddTransition(AIStateCondition* toAdd);
	void SetStartState(AIState* toSetAdd);

private:
	std::vector<AIState*> m_States;
	std::vector<AIStateCondition*> m_conditions;
	AIState* m_ActiveState = nullptr;
};

//namespace  EL
//{
//	
//	class FSMState
//	{
//	public:
//		FSMState() {}
//		virtual ~FSMState() = default;
//
//		virtual void OnEnter(Blackboard* pBlackboard) {};
//		virtual void OnExit(Blackboard* pBlackboard) {};
//		virtual void Update(Blackboard* pBlackboard, float deltaTime) {};
//
//	};
//
//	class FSMTransition
//	{
//	public:
//		FSMTransition() = default;
//		virtual ~FSMTransition() = default;
//		virtual bool ToTransition(Blackboard* pBlackboard) const = 0;
//	};
//
//	class FiniteStateMachine
//	{
//	public:
//		FiniteStateMachine(FSMState* startState, Blackboard* pBlackboard);
//		virtual ~FiniteStateMachine();
//
//		void AddTransition(FSMState* startState, FSMState* toState, FSMTransition* transition);
//		virtual void Update(float deltaTime) override {};
//	//	Elite::Blackboard* GetBlackboard() const;
//
//	private:
//		void ChangeState(FSMState* newState);
//	private:
//		typedef std::pair<FSMTransition*, FSMState*> TransitionStatePair;
//		typedef std::vector<TransitionStatePair> Transitions;
//
//		std::map<FSMState*, Transitions> m_Transitions; //Key is the state, value are all the transitions for that current state 
//		FSMState* m_pCurrentState;
//	//	Blackboard* m_pBlackboard = nullptr; // takes ownership of the blackboard
//	};
//}

