#include "TronConstructor.h"

#include "ActorComponent.h"
#include "BouncingBulletComponent.h"
#include "CollisionComponent.h"
#include "ComponentList.h"
#include "EnemyTankComponent.h"
#include "HitboxManager.h"
#include "HurtBoxComponent.h"
#include "ScoreComponent.h"
#include "SquareComponent.h"
#include "TankControlComponent.h"
#include "TankFieldControlComponent.h"

#include "TankGunComponent.h"

std::shared_ptr<dae::GameObject> TronConstructor::PlayerTank()
{
	auto tank = std::make_shared<dae::GameObject>();

	//actor Logic
	auto ac = new ActorComponent();
	tank->AddComponent(ac);

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

std::shared_ptr<dae::GameObject> TronConstructor::TankGameFieldAlt(const std::string& , const std::string& PathJsonFile, glm::ivec2 SizeOfCell)//, const glm::ivec2& PathOffset)
{
	auto field = std::make_shared<dae::GameObject>();

	auto FieldControl = new TankFieldControlComponent();
	field->AddComponent(FieldControl);
	field->SetPosition(510, 360);
	
	FieldControl->CreateLinesWallsAlt(PathJsonFile,SizeOfCell);
	return field;
}

std::shared_ptr<dae::GameObject> TronConstructor::PlayerBullet(float Rotation)
{
	auto bullet = std::make_shared<dae::GameObject>();

	auto bulletImg = new RenderComponent();
	bulletImg->SetTexture("BulletPlayer.png");
	bulletImg->EnableOffset(true);
	bulletImg->SetOffset(-16, -16);
	bullet->AddComponent(bulletImg);

	auto BulletSquare = new SquareComponent();
	BulletSquare->SetSquare({ -5,-5,10,10 });
	bullet->AddComponent(BulletSquare);

	auto ac =new ActorComponent();
	bullet->AddComponent(ac);



	auto BulletCol = new CollisionComponent(BulletSquare,false,ac);
	bullet->AddComponent(BulletCol);


	auto BulletHurtBoxComponent = new HurtBoxComponent(BulletSquare,0);
	bullet->AddComponent(BulletHurtBoxComponent);


	auto bulletLogic = new BouncingBulletComponent(static_cast<float>(M_PI) * (Rotation-90.f)/ 180.f ,BulletCol,BulletHurtBoxComponent,ac,25);
	bullet->AddComponent(bulletLogic);

	return bullet;

}

std::shared_ptr<dae::GameObject> TronConstructor::EnemyTank()
{
	auto EnemyTank = std::make_shared<dae::GameObject>();

	//The Body
	auto BodyRender = new RenderComponent();
	EnemyTank->AddComponent(BodyRender);
	BodyRender->SetTexture("TankBlueVert.png");
	BodyRender->SetOffset(-16, -16);
	//auto Hitbox = new HitBoxComponent();

	auto Sqr = new SquareComponent();
	EnemyTank->AddComponent(Sqr);
	Sqr->SetSquare({ -18,-18,34,34 });
	


	auto Hitbox = new HitboxComponent(Sqr,0);
	EnemyTank->AddComponent(Hitbox);
	dae::HitBoxManager::GetInstance().addHitBox(Hitbox);

	auto SightSqr = new SquareComponent();
	EnemyTank->AddComponent(SightSqr);

	auto Sight = new EnemySightComponent(SightSqr);
	EnemyTank->AddComponent(Sight);

	auto EnemyTankControl = new EnemyTankComponent(Hitbox,Sight);
	EnemyTank->AddComponent(EnemyTankControl);


	return EnemyTank;

}

std::shared_ptr<dae::GameObject> TronConstructor::ScoreObject()
{

	auto obj = std::make_shared<dae::GameObject>();

	auto render = new RenderComponent();
	obj->AddComponent(render);

	auto text = new dae::TextComponent("Text",,render);
	obj->AddComponent(text);

	auto score = new ScoreComponent();
	obj->AddComponent(score);

	return obj;
}


