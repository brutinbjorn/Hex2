#pragma once
#include "BaseComponent.h"
class HealthComponent :
	public BaseComponent
{

public:
	HealthComponent(int health) : m_health(health), m_MaxHealth(health)
	{

	};
	void Initialize() override {};
	void FixedUpdate(const float ) override {};
	void Update(const float) override {};
	void Render() const override {};
	void LateUpdate(const float ) override{};

	int GetHealth() const noexcept { return  m_health; };
	int GetMaxHealth() const { return m_MaxHealth; };
	void LoseHealth(int damage) { m_health -= damage; };
	void SetHealth(int newHealth) { m_health = newHealth;  };
private:
	int m_health;
	int m_MaxHealth;

};

