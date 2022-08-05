#pragma once
#include "BaseComponent.h"

#include "Transform.h"
#include "glm/glm.hpp"
#include "SDL.h"

namespace dae
{
	class Texture2D;
}

class RenderComponent :
    public BaseComponent
{
public:
	RenderComponent() = default;
	~RenderComponent() override;

	void Initialize() override{};

	void FixedUpdate(const float) override {};
	void Update(const float) override {};
	void LateUpdate(const float) override{};
	void Render() const override;
	void GuiRender() const override {};


	//void SetPosition(float x, float y, float z = 0);
	//void SetPosition(glm::vec3 pos);

	//SDL SetsSizes in pixels
	//seting 1 of the 2 to zero resets it to normal size
	void SetSize(int x, int y);
	void SetOffset(int x, int y);
	glm::vec2 GetOffset() const { return m_offset; };

	void SetRotation(double rot) { m_Rotation = rot; };
	void SetTexture(const std::string & filename);
	void SetTexture(dae::Texture2D * texture2D);
	bool Recieve(BaseComponent* , const std::string& ) override;
	//void SetSourceRect(SDL_Rect rect);

protected:
	dae::Texture2D* m_pTexture = nullptr;
	SDL_Rect* m_pSrcRect = nullptr;

	//SDL_Cir*
	//transform value in RenderComp & gameObject, consider using the gameObject transform or renaming/reusing. translate? offset?

	//RECONS the render now asks his parent if it gots a transform, uses it as a base and adds its offset ontop of it.
	//dae::Transform m_transform;

	bool m_IsSizeSet = false;
	bool m_IsBoundToOtherComp = false;
	glm::ivec2 m_Size{0,0};
	glm::ivec2 m_offset{ 0,0 };
	double m_Rotation = 0.0;
};

