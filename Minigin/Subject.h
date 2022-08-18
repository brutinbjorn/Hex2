#pragma once
#include "Observer.h"
#include "algorithm"
class BaseComponent;

class Subject
{
public:
	Subject(){};

	void AddObserver(InterFace::Observer* newObserver)
	{
		m_observers.push_back(newObserver);
		m_numberObservers++;
	}
	void RemoveObserver(InterFace::Observer* oldObserver)
	{
		auto val = std::remove(m_observers.begin(),m_observers.end(), oldObserver);
		m_numberObservers--;

	}

	void Notify( const std::string& msg)
	{
		for (int i = 0; i < m_numberObservers; i++)
		{
			m_observers[i]->OnNotify( msg);
		}
	}

protected:
	std::vector<InterFace::Observer*> m_observers{};
	int m_numberObservers = 0;

};

