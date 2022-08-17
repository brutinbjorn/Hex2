#pragma once
#include <BaseComponent.h>

#include "SquareComponent.h"
#include "ENUMS.h"

class EnemySightComponent :
    public BaseComponent
{
public:
	EnemySightComponent(SquareComponent* SightSquare);
	~EnemySightComponent() = default;
	EnemySightComponent(const EnemySightComponent& other) = delete;
	EnemySightComponent(EnemySightComponent&& other) noexcept = delete;
	EnemySightComponent& operator=(const EnemySightComponent& other) = delete;
	EnemySightComponent& operator=(EnemySightComponent&& other) noexcept = delete;

	void Initialize() override {};
	void FixedUpdate(const float ) override {};
	void Update(const float ) override ;
	void LateUpdate(const float ) override {};
	void Render() const override {};

	void SetDirection(Directions dir)
	{
		m_Direction = dir;

		switch (m_Direction)
		{
		case DIRECTION_DOWN:
			nm_pSightSquare->SetSquare({ witdhOfBeam / 2,-lengthOfBeam ,witdhOfBeam,lengthOfBeam });
			break;
		case DIRECTION_UP:
			nm_pSightSquare->SetSquare({ witdhOfBeam / 2,0,witdhOfBeam,lengthOfBeam });
			break;
		case DIRECTION_LEFT:
			nm_pSightSquare->SetSquare({ -lengthOfBeam,-witdhOfBeam/2,lengthOfBeam,witdhOfBeam });
			break;
		case DIRECTION_RIGHT:
			nm_pSightSquare->SetSquare({ 0,-witdhOfBeam / 2,lengthOfBeam,witdhOfBeam });
			break;
		default: ;
		}

	};
	
private:
	SquareComponent* nm_pSightSquare = nullptr;
	bool m_SeeingPLayer = false;
	Directions m_Direction = DIRECTION_NONE;
	int lengthOfBeam = 200;
	int witdhOfBeam = 4;
};

