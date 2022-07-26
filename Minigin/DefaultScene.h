#pragma once
#include "Scene.h"
class DefaultScene :
    public dae::Scene
{
public:
	DefaultScene(std::string name) : Scene(name){};

	//DefaultScene() = default;
	~DefaultScene() override = default;
	DefaultScene(const DefaultScene& other) = delete;
	DefaultScene(DefaultScene&& other) noexcept = delete;
	DefaultScene& operator=(const DefaultScene& other) = delete;
	DefaultScene& operator=(DefaultScene&& other) noexcept = delete;


	void Initialize() override;
};

