#pragma once
#include "MiniginPCH.h"
class Observer;
struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		void Initialize() ;
		void Cleanup();
		void Run();

		virtual void LoadGame();
		void FixedUpdate(const float ft);
		void Update(const float deltaTime);
		void LateUpdate(const float deltaTime);
		
		void Render() const;
	private:
		static const int MsPerFrame = 8; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		
	};
}