#pragma once
#include "Scene.h"

class TankGameScene final :public dae::Scene
{
public:

	explicit TankGameScene(const std::string& name);
	~TankGameScene() = default;
	//TankGameScene(const TankGameScene& other) = default;
	//TankGameScene(TankGameScene&& other) noexcept = default;
	//TankGameScene& operator=(const TankGameScene& other) = default;
	//TankGameScene& operator=(TankGameScene&& other) noexcept = default;

	void Initialize() override;
};

