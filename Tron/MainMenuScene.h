#pragma once
#include "Scene.h"

class MainMenuScene final : public dae::Scene
{
public:
	explicit MainMenuScene(const std::string& name);
	~MainMenuScene() override = default;
	//TankGameScene(const TankGameScene& other) = default;
	//TankGameScene(TankGameScene&& other) noexcept = default;
	//TankGameScene& operator=(const TankGameScene& other) = default;
	//TankGameScene& operator=(TankGameScene&& other) noexcept = default;

	void Initialize() override;
};

