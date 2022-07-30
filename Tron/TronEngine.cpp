#include "TronEngine.h"
//#include "TronConstructor.h"
#include "TankGameScene.h"

void TronEngine::LoadGame()
{
	auto tankScene = std::shared_ptr<dae::Scene>(new TankGameScene("TankScene"));
	dae::SceneManager::GetInstance().AddScene(tankScene);
	tankScene->Initialize();
}
