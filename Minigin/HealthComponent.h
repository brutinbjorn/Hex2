#pragma once
#include "BaseComponent.h"
#include "Observer.h"

class HealthComponent :
	public BaseComponent,public InterFace::Observer
{

public:
	HealthComponent(int health) : m_health(health), m_MaxHealth(health)
	{

	};
	void Initialize() override {};
	void FixedUpdate(const float ) override {};
	void Update(const float) override
	{
		if(m_HealthChanged)
			m_HealthChanged = false;
	};
	void Render() const override {};
	void LateUpdate(const float ) override{};

	int GetHealth() const noexcept { return  m_health; };
	int GetMaxHealth() const { return m_MaxHealth; };
	void LoseHealth(int damage) { m_health -= damage; };
	void SetHealth(int newHealth) { m_health = newHealth;  };

	bool HasChanged() const { return m_HealthChanged; };
	void OnNotify(const std::string& msg) override;
	
private:
	bool m_HealthChanged = false;
	int m_health;
	int m_MaxHealth;

};

