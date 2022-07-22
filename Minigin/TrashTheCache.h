#pragma once
#include "imgui_plot.h"

class TrashTheCache
{
public:
	TrashTheCache() = default;
	~TrashTheCache() = default;
	void ExerciseOne();
	void ExerciseTwo();
	//void ExerciseTree();

private:
	//int m_SamplesOne = 100;
	//int m_SamplesTwo = 100;

	bool m_ButtonOne = false;
	bool m_ButtonTwo = false;
	bool m_ButtonTree = false;

	bool m_ButtonGameObject = false;
	bool m_ButtonGameObjectAlt = false;

	bool m_PlotGeneratedOne = false;
	bool m_PlotGeneratedTwo = false;
	bool m_PlotGeneratedTree = false;

	//inline static int M_total = 20;
	float m_SamplesTakenOne[15];
	float m_SamplesTakenTwo[15];
	float m_SamplesTakenThree[15];

	float m_Largest = 0;

	ImGui::PlotConfig m_plot1;
	ImGui::PlotConfig m_plot2;
	ImGui::PlotConfig m_plot3;


};

