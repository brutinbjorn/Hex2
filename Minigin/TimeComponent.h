#pragma once
#include <chrono>
#include "BaseComponent.h"

class TimeComponent final:
    public BaseComponent
{
public:
	TimeComponent();
	~TimeComponent() override = 0;

	TimeComponent(const TimeComponent&) = default;
	TimeComponent(TimeComponent&&) = default;

	void start();
	void Initialize() override {};
	void FixedUpdate(const float dt) override;
	void Update(const float) override{};
	void Render() const override{};

	uint32_t getFPS() const { return m_FPS; };
	float GetDeltaTime() const { return m_DeltaTime; };
	bool IsRunning() const { return m_IsRunning; };
private:
	std::chrono::high_resolution_clock m_HClock = std::chrono::high_resolution_clock();
	std::chrono::steady_clock::time_point m_currentTime;
	std::chrono::steady_clock::time_point m_lastTime;

	uint32_t m_lag;
	uint32_t m_FPS;
	uint32_t m_FPSCount;
	float m_FPSTimer;
	float m_TotalTime;
	float m_DeltaTime;
	float m_ElapsedTime;
	float m_PrintTimer;
	bool m_IsRunning = false;
	bool m_PrintTimeConsole = false;
};

