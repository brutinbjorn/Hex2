#include "MiniginPCH.h"
#include "Minigin.h"

//#include <steam_api_common.h>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"


#include "GameObject.h"
#include "ObjectConstructor.h"
#include "ComponentList.h"
#include "HealthBarComponent.h"
#include "JsonManager.h"

#include "Scene.h"
#include "ScoreComponent.h"

#include "Subject.h"
#include "TimeManager.h"
#include "ServiceLocator.h"


using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1020, 
		720,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

#ifdef USE_SDLMIXER2
	ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());
#endif

}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() 
{
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");


	auto& ss = ServiceLocator::GetSoundSystem();

	ss.LoadSound(0, "GameMusic.mp3");
	ss.PlaySound(0, 0.5f );
	ss.LoadSound(1, "03 Level End.mp3");
	ss.PlaySound(1, 0.5f);


	auto& input = InputManager::GetInstance();

	Action thunder = Action();
	thunder.type = InputType::WentDown;
	thunder.XButton = XBox360Controller::ControllerButton::ButtonA;
	thunder.key = SDL_SCANCODE_T;
	thunder.pCommand = new FireCommand();
	input.AddAction(thunder);

	Action clap = Action();
	clap.type = InputType::WentUp;
	clap.XButton = XBox360Controller::ControllerButton::ButtonA;
	clap.key = SDL_SCANCODE_T;
	clap.pCommand = new FartCommand();
	input.AddAction(clap);



	//auto background = std::make_shared<GameObject>();
	//RenderComponent* backgroundImage = new RenderComponent();
	//backgroundImage->SetTexture("Background.jpg");
	//background->AddComponent(backgroundImage);
	//scene.AddGameObject(background);



	//auto logo = std::make_shared<GameObject>();
	//RenderComponent* logoImage = new RenderComponent();
	//logoImage->SetTexture("logo.png");
	//logoImage->SetOffset(0, 0);
	//logo->AddComponent(logoImage);
	//logo->SetPosition(216, 180);
	//scene.AddGameObject(logo);


//	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//auto TextObject = std::make_shared<GameObject>();
	//auto textRender = new RenderComponent();
	//TextObject->AddComponent(textRender);

	//auto textComp = new TextComponent("Programming 4 Assignment", font,textRender);
	//TextObject->AddComponent(textComp);
	//TextObject->SetPosition(80, 20);
	//scene.AddGameObject(TextObject);

	//auto FPSObject = std::make_shared<GameObject>();
	//auto fpsRender = new RenderComponent();
	//FPSObject->AddComponent(fpsRender);

	//auto fpsText = new TextComponent("FPS: 0",font,nullptr);
	//FPSObject->AddComponent(fpsText);
	//fpsText->SetColor(255, 255, 0);
	//auto fpsLogic = new FPSComponent();
	//FPSObject->AddComponent(fpsLogic);
	//scene.AddGameObject(FPSObject);




	//auto HealthBar = ObjectConstructor::HealthBar(glm::vec3{100,100,0},font);
	//scene.AddGameObject(HealthBar);

	//auto ScoreBar = ObjectConstructor::ScoreBar(glm::vec3{ 100,130,0 }, font);
	//scene.AddGameObject(ScoreBar);

	//auto PeterBurger = ObjectConstructor::BasicActor();
	//scene.AddGameObject(PeterBurger);

	//auto pep = PeterBurger->GetComponent<PeterPepperComponent>();

	//Action Die = Action();
	//Die.pCommand = new DieCommand(pep);
	//Die.key = SDL_SCANCODE_D;
	//Die.XButton = XBox360Controller::ControllerButton::DPadDown;
	//Die.type = InputType::WentUp;
	//InputManager::GetInstance().AddAction(Die);

	//Action Score = Action();
	//Score.pCommand = new ScoreTestCommand(pep);
	//Score.key = SDL_SCANCODE_S;
	//Score.XButton = XBox360Controller::ControllerButton::DPadLeft;
	//Score.type = InputType::WentUp;
	//InputManager::GetInstance().AddAction(Score);


	//auto playerScoreOb = new ScoreObserver(ScoreBar->GetComponent<ScoreComponent>());
	//auto m_pPlayerOp = new LivesObserver(HealthBar->GetComponent<HealthBarComponent>());

	//m_pObservers.push_back(ScoreBar->GetComponent<ScoreComponent>());
	//m_pObservers.push_back(HealthBar->GetComponent<HealthBarComponent>());
	//pep->GetSubject()->AddObserver(HealthBar->GetComponent<HealthBarComponent>());
	//pep->GetSubject()->AddObserver(ScoreBar->GetComponent<ScoreComponent>());

	//Player 2
	//auto HealthBar2 = ObjectConstructor::HealthBar(glm::vec3{ 100,280,0 }, font);
	//scene.AddGameObject(HealthBar2);

	//auto ScoreBar2 = ObjectConstructor::ScoreBar(glm::vec3{ 100,310,0 }, font);
	//scene.AddGameObject(ScoreBar2);

	//auto PeterBurger2 = ObjectConstructor::BasicActor();
	//scene.AddGameObject(PeterBurger2);

	//auto pep2 = PeterBurger2->GetComponent<PeterPepperComponent>();

	//Action Die2 = Action();
	//Die2.pCommand = new DieCommand(pep2);
	//Die2.key = SDL_SCANCODE_DOWN;
	////Die.XButton = XBox360Controller::ControllerButton::DPadDown;
	//Die2.type = InputType::WentUp;
	//InputManager::GetInstance().AddAction(Die2);

	//Action Score2 = Action();
	//Score2.pCommand = new ScoreTestCommand(pep2);
	//Score2.key = SDL_SCANCODE_UP;
	////Score.XButton = XBox360Controller::ControllerButton::DPadLeft;
	//Score2.type = InputType::WentUp;
	//InputManager::GetInstance().AddAction(Score2);


	////auto playerScoreOb2 = new ScoreObserver(ScoreBar2->GetComponent<ScoreComponent>());
	////auto m_pPlayerOp2 = new LivesObserver(HealthBar2->GetComponent<HealthBarComponent>());

	////m_pObservers.push_back(ScoreBar2->GetComponent<ScoreComponent>());
	////m_pObservers.push_back(m_pPlayerOp2);
	//pep2->GetSubject()->AddObserver(HealthBar2->GetComponent<HealthBarComponent>());
	//pep2->GetSubject()->AddObserver(ScoreBar2->GetComponent<ScoreComponent>());


	//// test to see if text cant send stuff to aa render.
	////auto delTest = std::make_shared<GameObject>();
	//auto deltextTest = new TextComponent("Test", font, nullptr);
	//delTest->AddComponent(deltextTest);
	//scene.AddGameObject(delTest);


}


void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	ServiceLocator::CleanUpSoundSystem();

	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	JsonManager::GetInstance().Init("../Data/");
	TimeManager::GetInstance().init();
	TimeManager::GetInstance().PrintTime(true);
	TimeManager::GetInstance().start();

	LoadGame();
	{

		auto& input = dae::InputManager::GetInstance();
		auto& time = dae::TimeManager::GetInstance();

		
		SceneManager::GetInstance().PostInitialize();
		bool doContinue = true;
		while (doContinue)
		{
			//SteamAPI_RunCallbacks();
			time.Update();

			doContinue = input.ProcessInput();

			while(time.ShouldDoFixedUpdateAndLowerLag())
			{
				float ft = time.GetMsPerUpdate();
				FixedUpdate(ft);
			}

			float dt = time.GetDeltaTime();

			Update(dt);
			Render();
		}
	}

	Cleanup();
}

void dae::Minigin::FixedUpdate(const float ft)
{
	SceneManager::GetInstance().FixedUpdate(ft);
}



void dae::Minigin::Update(const float deltaTime)
{
	SceneManager::GetInstance().Update(deltaTime);
}

void dae::Minigin::LateUpdate(const float lt)
{
	SceneManager::GetInstance().LateUpdate(lt);
}

void dae::Minigin::Render() const
{
	Renderer::GetInstance().Render();
}
