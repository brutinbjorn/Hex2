#include "TronConstructor.h"

#include "BouncingBulletComponent.h"
#include "CollisionComponent.h"
#include "ComponentList.h"
#include "SquareComponent.h"
#include "TankControlComponent.h"
#include "TankFieldControlComponent.h"

#include "TankGunComponent.h"

std::shared_ptr<dae::GameObject> TronConstructor::PlayerTank()
{
	auto tank = std::make_shared<dae::GameObject>();

	//The Body
	auto BodyRender = new RenderComponent();
	tank->AddComponent(BodyRender);
	BodyRender->SetTexture("TankRedVert.jpg");
	BodyRender->SetOffset(-16, -16);
	//auto Hitbox = new HitBoxComponent();

	//The Gun
	auto GunRender = new RenderComponent();
	tank->AddComponent(GunRender);
	GunRender->SetTexture("TankCannonRed.png");
	GunRender->SetOffset(-(8), -(23));
	GunRender->SetRotationPoint(SDL_Point{ 8,23 });

	auto scene = dae::SceneManager::GetInstance().GetScene("TankScene");

	auto GunLogic = new TankGunComponent(scene);
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



	return field;
}

std::shared_ptr<dae::GameObject> TronConstructor::PlayerBullet(float Rotation)
{
	auto bullet = std::make_shared<dae::GameObject>();

	auto bulletImg = new RenderComponent();
	bulletImg->SetTexture("BulletPlayer.png");
	bulletImg->EnableOffset(true);
	bulletImg->SetOffset(-16, 16);
	bullet->AddComponent(bulletImg);

	auto BulletSquare = new SquareComponent();
	BulletSquare->SetSquare({ -5,-5,10,10 });
	bullet->AddComponent(BulletSquare);
	auto BulletCol = new CollisionComponent(BulletSquare);
	bullet->AddComponent(BulletCol);

	auto bulletLogic = new BouncingBulletComponent(Rotation,BulletCol);
	bullet->AddComponent(bulletLogic);



	return bullet;

}
