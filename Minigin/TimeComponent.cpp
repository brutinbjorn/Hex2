#include "MiniginPCH.h"
#include "TimeComponent.h"

TimeComponent::TimeComponent() : m_lag(0),
	m_FPS(0), m_FPSCount(0), m_FPSTimer(0.0f),
	m_TotalTime(0.0f), m_DeltaTime(0),
	m_ElapsedTime(0), m_PrintTimer(0.f)
{
	m_HClock = std::chrono::high_resolution_clock();
	m_currentTime = m_HClock.now();
	m_lastTime = m_HClock.now();
}

void TimeComponent::FixedUpdate(const float)
{
	if (!m_IsRunning)
	{
		m_TotalTime = uint32_t(0.f);
		m_DeltaTime = uint32_t(0.f);
	}
	else
	{
		m_currentTime = m_HClock.now();
		m_DeltaTime = std::chrono::duration<float>(m_currentTime - m_lastTime).count();

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
