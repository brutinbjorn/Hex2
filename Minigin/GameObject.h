#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include <vector>

namespace dae
{
	//class Texture2D;
	//RECONS should the gameObject also be a child of baseComponent?
	//it would allow the GameObject itself to contain children, might also fix the problem of comps who shotgun messages to every compoment, by making subgroups allowing stuff to be split up.
	//problem would be how GameObject and its child objects should communicate, 

	class GameObject final
	{
	public:

		GameObject() = default;
		~GameObject();

		void Initialize();
		void FixedUpdate(const float ft) ;
		void Update(const float dt) ;
		void LateUpdate(const float lt) ;

		void Render() const ;

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		dae::Transform* GetTransform()  { return &m_Transform; };

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <typename T>
		T* GetComponent();
		void AddComponent(BaseComponent* ToAdd);


		//REDUNDENT send function, cleanup, change or remove.

		bool Send( BaseComponent* sender, const std::string& msg);
		bool Recieve( BaseComponent* sender, const std::string& msg);

	private:
		void SetChild(BaseComponent* child);
		void RemoveChild(BaseComponent* child);
		std::vector<BaseComponent*> m_pComponents = std::vector<BaseComponent*>();
		//std::vector<GameObject*> m_pChildObjects = std::vector<Gamo>

		Transform m_Transform;
		bool m_MarkForDeletion = false;


	};


	template <typename T>
	T* GameObject::GetComponent()
	{
		for (BaseComponent* bc: m_pComponents)
		{
			if (dynamic_cast<T*>(bc))
				return dynamic_cast<T*>(bc);
		}
		return nullptr;
	}
}

