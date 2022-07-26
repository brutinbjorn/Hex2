#include "MiniginPCH.h"
#include "TimeManager.h"
#include "math.h"

void dae::TimeManager::init()
{
	m_HClock = std::chrono::high_resolution_clock();
	m_currentTime = m_HClock.now();
	m_lastTime = m_HClock.now();
	m_DeltaTime = 0;
	m_ElapsedTime = 0;
	m_FPSTimer = 0.0f;
	m_FPS = 0;
	m_FPSCount = 0;
	m_lag = 0;
	m_TotalTime = 0.0f;
	m_PrintTimer = 0.f;
}

void dae::TimeManager::start()
{
	m_IsRunning = true;
	m_lastTime = m_HClock.now();
}

void dae::TimeManager::Update()
{
	if (!m_IsRunning)
	{
		m_TotalTime = 0.f;
		m_DeltaTime = 0.f;
	}
	else
	{
		m_currentTime = m_HClock.now();
		m_DeltaTime = std::chrono::duration<float>(m_currentTime - m_lastTime).count();

		m_lag += m_DeltaTime;

	
		m_FPSTimer += m_DeltaTime;
		++m_FPSCount;

		if (m_FPSTimer >= 1.0f)
		{
			m_FPS = m_FPSCount;
			m_FPSCount = 0;
			m_FPSTimer -= 1.f;
		}

		m_lastTime = m_currentTime;
	}


	if (m_PrintTimeConsole)
	{
		m_PrintTimer += m_DeltaTime;
		if (m_PrintTimer >= 1.f)
		{
			m_PrintTimer -= 1.f;
			std::cout << m_FPS << std::endl;
		}
	}

}

void dae::TimeManager::PrintTime(bool DoPrint)
{
	m_PrintTimeConsole = DoPrint;
}

// lowers the lag count
 bool dae::TimeManager::ShouldDoFixedUpdateAndLowerLag() 
{
	if (m_lag > m_msPerUpdate)
	{
		m_lag -= m_msPerUpdate;
		return true;
	}
	return false;

}