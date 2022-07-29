#pragma once
#include "ComponentList.h"

class TankFieldGridComponent final : public BaseComponent
{
public:
	TankFieldGridComponent() = default;
	~TankFieldGridComponent() = default;
	TankFieldGridComponent(const TankFieldGridComponent& other) = delete;
	TankFieldGridComponent(TankFieldGridComponent&& other) noexcept = delete;
	TankFieldGridComponent& operator=(const TankFieldGridComponent& other) = delete;
	TankFieldGridComponent& operator=(TankFieldGridComponent&& other) noexcept = delete;
private:

	int Size;
	int m_Rows = 10;
	int m_Collums = 10;



};

