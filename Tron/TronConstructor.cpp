#include "TronConstructor.h"
#include "ComponentList.h"
#include "TankControlComponent.h"

std::shared_ptr<dae::GameObject> ObjectConstructor::PlayerTank()
{
	auto tank = std::make_shared<dae::GameObject>();

	auto BodyRender = new RenderComponent();
	tank->AddComponent(BodyRender);
	BodyRender->SetTexture("");


	auto GunRender = new RenderComponent();
	tank->AddComponent(GunRender);
	GunRender->SetTexture("");

	auto TankControls = new TankControlComponent(BodyRender,GunRender);
	tank->AddComponent(TankControls);


	return tank;


}
