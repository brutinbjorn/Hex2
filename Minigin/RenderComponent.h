#pragma once
#include "BaseComponent.h"

#include "Transform.h"
#include "glm/glm.hpp"
#include "SDL.h"

namespace dae
{
	class Texture2D;
}
enum RenderSettings
{
	USE_OFFSET = 0b1,
	USE_ROTATION = 0b10,
	USE_CUSTOM_SIZE = 0b100,
	USE_TEXTURE_OFFSET = 0b1000
};

class RenderComponent final:
    public BaseComponent
{
public:
	RenderComponent();
	~RenderComponent() override;

	void Initialize() override{};

	void FixedUpdate(const float) override {};
	void Update(const float) override {};
	void LateUpdate(const float) override{};
	void Render() const override;
	void GuiRender() const override {};

	//Texture
	void SetTexture(const std::string & filename);
	void SetTexture(dae::Texture2D * texture2D);

	//Size
	void SetSize(int x, int y);
	glm::ivec2 GetTextureSize() const;

	//Offset
	void EnableOffset(bool IsTrue = true) { m_useOffset = IsTrue; };
	void SetOffset(int x, int y);
	glm::vec2 GetOffset() const { return m_offset; };

	//rotation
	void EnableRotation(bool Istrue = false) { m_RotateTrue = Istrue; };
	void SetRotation(float rot) { m_Rotation = rot; };
	float GetRotation() const { return m_Rotation; };
	void SetRotationPoint(const SDL_Point& point) { m_RotationPoint = point; };
	const SDL_Point& GetRotationPoint() const { return m_RotationPoint; };

	bool Recieve(BaseComponent* , const std::string& ) override;
	

	void SetActive(bool active) { m_Active = active; }
	bool GetActive() const { return m_Active; }

private:
	dae::Texture2D* m_pTexture = nullptr;
	SDL_Rect* m_pSrcRect = nullptr;

	SDL_Point m_RotationPoint = { 0,0 };

	bool m_useOffset = true;
	glm::ivec2 m_offset{ 0,0 };
	glm::ivec2 m_Size{0,0};

	char m_RenderSettings = 0b1111111 - USE_CUSTOM_SIZE;

	bool m_RotateTrue = false;
	bool m_IsSizeSet = false;
	bool m_IsBoundToOtherComp = false;
	float m_Rotation = 0.0;

	bool m_Active = true;



};

