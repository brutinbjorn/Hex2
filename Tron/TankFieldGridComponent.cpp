#include "TankFieldGridComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "TankFieldLineComponent.h"

TankFieldGridComponent::TankFieldGridComponent(const SDL_Rect& Rect)
	:m_Rectangle(Rect),m_Rows(10),m_Collums(10)
{
}

//void TankFieldGridComponent::Initialize()
//{
//
//	//auto spaceBetweenRows = m_Rectangle.h / 12;
//
//
//	//for (int i = 0; i < m_Rows; ++i)
//	//{
//	//	m_TankFieldLines<>
//	//}
//}

void TankFieldGridComponent::CreateLinesEven()
{

	auto heightBetweenLines = m_Rows + 2 / m_Rectangle.h;
	auto WidthBetweenCollums = m_Collums + 2 / m_Rectangle.w;

	for (int iRow = 0; iRow < m_Rows; ++iRow)
	{
		for (int iCollum = 0; iCollum < m_Collums; ++iCollum)
		{
			auto newLine = std::make_shared<dae::GameObject>();
			auto LineField = new TankFieldLineComponent();

			newLine->GetTransform()->SetPosition(static_cast<float>(WidthBetweenCollums * (1 + iRow)), static_cast<float>(heightBetweenLines * (1 + iCollum)), 0);

			//glm::vec2 pos = { (iCollum + 1) * WidthBetweenCollums ,(iRow + 1) * heightBetweenLines };

			auto sqr = SDL_Rect{ WidthBetweenCollums/2,3,WidthBetweenCollums,6 };


			LineField->SetSquare(sqr);
			newLine->AddComponent(LineField);



		}
	}

}

void TankFieldGridComponent::CreateLinesFromFile()
{

}

void TankFieldGridComponent::Render() const
{
	dae::Renderer::GetInstance().RenderRect(m_Rectangle, SDL_Color{ 255,0,255,255 });
}
