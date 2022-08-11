#include "TronConstructor.h"
#include "ComponentList.h"
#include "TankControlComponent.h"
#include "TankFieldControlComponent.h"
#include "TankFieldGridComponent.h"
#include "TankGunComponent.h"

std::shared_ptr<dae::GameObject> TronConstructor::PlayerTank()
{
	auto tank = std::make_shared<dae::GameObject>();

	auto BodyRender = new RenderComponent();
	tank->AddComponent(BodyRender);
	BodyRender->SetTexture("TankRedVert.jpg");

	auto GunRender = new RenderComponent();
	tank->AddComponent(GunRender);
	GunRender->SetTexture("TankCannonRed.png");
	GunRender->SetOffset(-7, 10);

	auto GunLogic = new TankGunComponent();
	GunLogic->LinkGunTexture(GunRender);
	tank->AddComponent(GunLogic);


	auto TankControls = new TankControlComponent(BodyRender,GunRender);
	tank->AddComponent(TankControls);
	return tank;


}

std::shared_ptr<dae::GameObject> TronConstructor::TankGameField(const std::string& BackgroundImg, const std::string& PathJsonFile)//, const glm::ivec2& PathOffset)
{
	auto field = std::make_shared<dae::GameObject>();

	auto bgImage = new RenderComponent();
	bgImage->SetTexture(BackgroundImg);

	auto size = bgImage->GetTextureSize();
	bgImage->SetOffset(-(size.x / 2), -(size.y / 2));

	field->AddComponent(bgImage);
	field->SetPosition(510, 360);// Center position of screen.

	auto FieldControl = new TankFieldControlComponent();
	field->AddComponent(FieldControl);
	FieldControl->CreateLinesAndWallsFromJsonFile(PathJsonFile,glm::ivec2{ -(size.x / 2), -(size.y / 2) });



	//AddGameObject(background);
	//former---<//
	//auto BackGround = new RenderComponent();
	//BackGround->SetTexture(BackgroundImg);
	//field->AddComponent(BackGround);
	//auto FieldLogic = new TankFieldGridComponent();
	//Fie




	return field;
}
