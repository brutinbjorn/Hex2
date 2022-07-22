


#include "BurgerTime.h"

#include "InputManager.h"
#include "BurgerTimeCommands.h"
#include "JsonManager.h"
#include "MoveGridComponent.h"
#include "ObjectConstructor.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "BurgerTimeFactory.h"

void BurgerTime::LoadGame()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//auto& ss = ServiceLocator::GetSoundSystem();

	//ss.LoadSound(0, "GameMusic.mp3");
	//ss.PlaySound(0, 0.5f);
	//ss.LoadSound(1, "03 Level End.mp3");
	//ss.PlaySound(1, 0.5f);

	//auto& input = dae::InputManager::GetInstance();

	//dae::Action thunder = dae::Action();
	//thunder.type = dae::InputType::WentDown;
	//thunder.XButton = XBox360Controller::ControllerButton::ButtonA;
	//thunder.key = SDL_SCANCODE_T;
	//thunder.pCommand = new FireCommand();
	//input.AddAction(thunder);

	//dae::Action clap = dae::Action();
	//clap.type = dae::InputType::WentUp;
	//clap.XButton = XBox360Controller::ControllerButton::ButtonA;
	//clap.key = SDL_SCANCODE_T;
	//clap.pCommand = new FartCommand();
	//input.AddAction(clap);



	auto background = std::make_shared<dae::GameObject>();
	RenderComponent* backgroundImage = new RenderComponent();
	backgroundImage->SetTexture("stage-1.png");
	backgroundImage->SetSize(720, 720);		//1020,720
	backgroundImage->SetOffset(1020/2, 720/2);
	background->AddComponent(backgroundImage);
	scene.AddGameObject(background);





	glm::vec2 offset = {150,0};
	auto MovementGrid = std::make_shared<dae::GameObject>();
	scene.AddGameObject(MovementGrid);
	MoveGridComponent* grid = new MoveGridComponent("Grid.json",offset);
	MovementGrid->AddComponent(grid);
	//SDL_Rect TestQuad;
	//TestQuad.w = 720;
	//TestQuad.h = 20;
	//TestQuad.x = 150;
	//TestQuad.y = 25;

	//char PosDir = static_cast<char>(left + right);
	//MoveZoneComponent* testZone = new MoveZoneComponent(TestQuad,PosDir);
	//testZone->SetDebugRender(true);
	//MovementGrid->AddComponent(testZone);
	//grid->AddZone(testZone);



	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//auto HealthBar = ObjectConstructor::HealthBar(glm::vec3{ 100,100,0 }, font);
	//scene.AddGameObject(HealthBar);

	//auto ScoreBar = ObjectConstructor::ScoreBar(glm::vec3{ 100,130,0 }, font);
	//scene.AddGameObject(ScoreBar);

	auto PeterBurger = ObjectConstructor::BasicActor("PeterPepper.png");
	PeterBurger->SetPosition(360, 551);

	scene.AddGameObject(PeterBurger);
	auto pep = PeterBurger->GetComponent<ActorComponent>();

	//PeterBurger->AddComponent(new PeterPepperComponent());
	auto renderer = PeterBurger->GetComponent<RenderComponent>();
	renderer->SetSize(32, 32);

	//pep. 


	std::vector<int> Heights = {47, 278, 451,566};
	std::vector <std::string> Textures = {"BunTop.png","Sla.png","Meat.png","BunBottom.png"};

	auto Burger = BurgerTimeFactory::Burger(glm::ivec2(150+111,720-19),glm::ivec2(116,19),Heights,Textures);
	scene.AddGameObject(Burger);





#pragma region Controls
	dae::Action MoveDown;
	MoveDown.pCommand = new MoveCommand(pep,0,1);
	MoveDown.key = SDL_SCANCODE_DOWN;
	MoveDown.XButton = XBox360Controller::ControllerButton::DPadDown;
	MoveDown.type = dae::InputType::IsPressed;
	dae::InputManager::GetInstance().AddAction(MoveDown);

	dae::Action MoveUp;
	MoveUp.pCommand = new MoveCommand(pep,0,-1);
	MoveUp.key = SDL_SCANCODE_UP;
	MoveUp.XButton = XBox360Controller::ControllerButton::DPadUp;
	MoveUp.type = dae::InputType::IsPressed;
	dae::InputManager::GetInstance().AddAction(MoveUp);

	dae::Action MoveLeft;
	MoveLeft.pCommand = new MoveCommand(pep, -1, 0);
	MoveLeft.key = SDL_SCANCODE_LEFT;
	MoveLeft.XButton = XBox360Controller::ControllerButton::DPadLeft;
	MoveLeft.type = dae::InputType::IsPressed;
	dae::InputManager::GetInstance().AddAction(MoveLeft);

	dae::Action MoveRight ;
	MoveRight.pCommand = new MoveCommand(pep, 1, 0);
	MoveRight.key = SDL_SCANCODE_RIGHT;
	MoveLeft.XButton = XBox360Controller::ControllerButton::DPadRight;
	MoveLeft.type = dae::InputType::IsPressed;
	dae::InputManager::GetInstance().AddAction(MoveRight);


	dae::Action PrintPos = dae::Action(new PrintCommand(), XBox360Controller::ControllerButton::Start, SDL_SCANCODE_6, dae::InputType::WentDown);
	dae::InputManager::GetInstance().AddAction(PrintPos);

	dae::Action MoveDownLock;
	MoveDownLock.pCommand = new LimitedMoveCommand(PeterBurger.get(), grid, 0, 1);
	MoveDownLock.key = SDL_SCANCODE_S;
	MoveDownLock.XButton = XBox360Controller::ControllerButton::DPadDown;
	MoveDownLock.type = dae::InputType::IsPressed;
	dae::InputManager::GetInstance().AddAction(MoveDownLock);

	dae::Action MoveUpLock;
	MoveUpLock.pCommand = new LimitedMoveCommand(PeterBurger.get(), grid, 0, -1);
	MoveUpLock.key = SDL_SCANCODE_W;
	MoveUpLock.XButton = XBox360Controller::ControllerButton::DPadUp;
	MoveUpLock.type = dae::InputType::IsPressed;
	dae::InputManager::GetInstance().AddAction(MoveUpLock);

	dae::Action MoveLeftLock;
	MoveLeftLock.pCommand = new LimitedMoveCommand(PeterBurger.get(), grid, -1, 0);
	MoveLeftLock.key = SDL_SCANCODE_A;
	MoveLeftLock.XButton = XBox360Controller::ControllerButton::DPadLeft;
	MoveLeftLock.type = dae::InputType::IsPressed;
	dae::InputManager::GetInstance().AddAction(MoveLeftLock);

	dae::Action MoveRightLock;
	MoveRightLock.pCommand = new LimitedMoveCommand(PeterBurger.get(),grid, 1, 0);
	MoveRightLock.key = SDL_SCANCODE_D;
	MoveRightLock.XButton = XBox360Controller::ControllerButton::DPadRight;
	MoveRightLock.type = dae::InputType::IsPressed;
	dae::InputManager::GetInstance().AddAction(MoveRightLock);
#pragma endregion 



	


	////auto playerScoreOb2 = new ScoreObserver(ScoreBar2->GetComponent<ScoreComponent>());
	////auto m_pPlayerOp2 = new LivesObserver(HealthBar2->GetComponent<HealthBarComponent>());

	////m_pObservers.push_back(ScoreBar2->GetComponent<ScoreComponent>());
	////m_pObservers.push_back(m_pPlayerOp2);
	//pep2->GetSubject()->AddObserver(HealthBar2->GetComponent<HealthBarComponent>());
	//pep2->GetSubject()->AddObserver(ScoreBar2->GetComponent<ScoreComponent>());


	// test to see if text cant send stuff to aa render.
	//auto delTest = std::make_shared<GameObject>();
	//auto deltextTest = new TextComponent("Test", font, nullptr);
	//delTest->AddComponent(deltextTest);
	//scene.AddGameObject(delTest);
}
