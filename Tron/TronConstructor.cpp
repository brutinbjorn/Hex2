#include "TronConstructor.h"
#include "ComponentList.h"
#include "TankControlComponent.h"

std::shared_ptr<dae::GameObject> TronConstructor::PlayerTank()
{
	auto tank = std::make_shared<dae::GameObject>();

	auto BodyRender = new RenderComponent();
	tank->AddComponent(BodyRender);
	BodyRender->SetTexture("TankRedVert.jpg");

	auto GunRender = new RenderComponent();
	tank->AddComponent(GunRender);
	GunRender->SetTexture("TankCannonRed.png");

	auto TankControls = new TankControlComponent(BodyRender,GunRender);
	tank->AddComponent(TankControls);

	tank->GetTransform()->SetPosition(40, 40, 0);
	return tank;


}

std::shared_ptr<dae::GameObject> TronConstructor::TankGameField()
{
	auto field = std::make_shared<dae::GameObject>();

	//auto fieldGrid = new;

	return field;
}
