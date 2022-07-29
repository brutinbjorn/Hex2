#pragma once
class WallComponent
{
public:
	WallComponent() = default;
	~WallComponent() = default;
	WallComponent(const WallComponent& other) = delete;
	WallComponent(WallComponent&& other) noexcept = delete;
	WallComponent& operator=(const WallComponent& other) = delete;
	WallComponent& operator=(WallComponent&& other) noexcept = delete;



};

