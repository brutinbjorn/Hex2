#include "MiniginPCH.h"
#include "TrashTheCache.h"

#include <chrono>

#include "imgui.h"


struct transform
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};

class GameObject3D
{
public:
	transform transform;
	int ID = 1;

};
class GameObject3DAlt
{
public:
	transform* transform;
	int ID = 1;

};


void TrashTheCache::ExerciseOne() 
{

	if (ImGui::Button("Trash the Cache"))
		m_ButtonOne = !m_ButtonOne;

	if(m_ButtonOne)
	{
		std::cout << "TrashTheCache!\n";


		static const int size = 10000000;
		int* buffer = new int[size];


		for (int i = 0; i < size; ++i)
		{
			buffer[i] = 1;
		}


		int stepIncreases = 0;
		float Largest = 0;

		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{

			long long average = 0;

			for (int av = 0; av < 10; ++av)
			{
				auto start = std::chrono::high_resolution_clock::now();
				for (int i = 0; i < size; i += stepsize)
				{
					buffer[i] *= 2;

				}
				auto end = std::chrono::high_resolution_clock::now();
				auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

				average += elapsed;

			}

			average /= 10;

			if (Largest < average)
				Largest = float(average);
			

			m_SamplesTakenOne[stepIncreases] = float(average);
			stepIncreases++;



	
			std::cout << "stepsize: " << stepsize << "Time taken in microsecs " << average << std::endl;
		}

		delete[]buffer;

		m_ButtonOne = false;
		ImGui::PlotConfig conf;

		m_plot1 = conf;
		//m_plot1.values.xs = x_data; // this line is optional
		m_plot1.values.ys = m_SamplesTakenOne;
		m_plot1.values.count = stepIncreases;
		m_plot1.scale.min = 0;
		m_plot1.scale.max = Largest;
		m_plot1.tooltip.show = true;
		m_plot1.tooltip.format = "x=%.2f, y=%.2f";
		m_plot1.grid_x.show = true;
		m_plot1.grid_y.show = true;
		m_plot1.frame_size = ImVec2(400, 400);
		m_plot1.line_thickness = 1.f;

		m_PlotGeneratedOne = true;

	}

	if (m_PlotGeneratedOne)
	{
		//ImGui::Begin("Trash the cashe", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Plot("plot1", m_plot1);

		//ImGui::End();
	}


}

void TrashTheCache::ExerciseTwo()
{
	//ImGui::BeginChild("Exec2");

	if (ImGui::Button("Trash the Cache with GameObjects"))
		m_ButtonTwo = !m_ButtonTwo;


	if(m_ButtonTwo)
	{
		static const int size = 10000000;
		std::vector<GameObject3D>* gameObjects = new std::vector<GameObject3D>();



		for (int i = 0; i < size; i++)
		{

			(*gameObjects).push_back(GameObject3D());
		}

		int stepIncreases = 0;
		float Largest = 0;
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			long long average = 0;

			for (int av = 0; av < 10; ++av)
			{
				auto start = std::chrono::high_resolution_clock::now();
				for (int i = 0; i < size; i += stepsize)
				{

					(*gameObjects)[i].transform.matrix[0] *= 2;

				}
				auto end = std::chrono::high_resolution_clock::now();
				auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

				average += elapsed;
			}

			average /= 10;

			if (Largest < average)
				Largest = float(average);

			if (Largest > m_Largest)
				m_Largest = Largest;


			m_SamplesTakenTwo[stepIncreases] = float(average);
			stepIncreases++;

			std::cout << "stepsize: " << stepsize << "Time taken in microsecs " << average << std::endl;
		}

		m_ButtonTwo = false;
		ImGui::PlotConfig conf;

		m_plot2 = conf;
		//m_plot1.values.xs = x_data; // this line is optional
		m_plot2.values.ys = m_SamplesTakenTwo;
		m_plot2.values.count = stepIncreases;
		m_plot2.scale.min = 0;
		m_plot2.scale.max = Largest;
		m_plot2.tooltip.show = true;
		m_plot2.tooltip.format = "x=%.2f, y=%.2f";
		//m_plot2.grid_x.show = true;
		//m_plot2.grid_y.show = true;
		m_plot2.frame_size = ImVec2(400, 400);
		m_plot2.line_thickness = 1.f;

		m_PlotGeneratedTwo = true;


		delete gameObjects;

	}


	if (m_PlotGeneratedTwo)
	{
		//ImGui::Begin("Trash the cashe", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Plot("plot2", m_plot2);

		//ImGui::End();
	}
	//ImGui::EndChild();


	//ImGui::BeginChild("Exec3");


	if (ImGui::Button("Trash the Cache with GameObjects ALT"))
		m_ButtonTree = !m_ButtonTree;

	if (m_ButtonTree)
	{
		static const int size = 10000000;
		std::vector<GameObject3DAlt>* gameObjects = new std::vector<GameObject3DAlt>();

		transform* newTrans = new transform();

		for (int i = 0; i < size; i++)
		{
			GameObject3DAlt newOB = GameObject3DAlt();

			newOB.transform = newTrans;
			(*gameObjects).push_back(newOB);
		}

		int stepIncreases = 0;
		float Largest = 0;
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			long long average = 0;

			for (int av = 0; av < 10; ++av)
			{
				auto start = std::chrono::high_resolution_clock::now();
				for (int i = 0; i < size; i += stepsize)
				{

					(*gameObjects)[i].ID *= 2;

				}
				auto end = std::chrono::high_resolution_clock::now();
				auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

				average += elapsed;
			}

			average /= 10;

			if (Largest < average)
				Largest = float(average);

			if (Largest > m_Largest)
				m_Largest = Largest;


			m_SamplesTakenThree[stepIncreases] = float(average);
			stepIncreases++;

			std::cout << "stepsize: " << stepsize << "Time taken in microsecs " << average << std::endl;
		}

		delete newTrans;

		m_ButtonTree = false;
		ImGui::PlotConfig conf;

		m_plot3 = conf;
		//m_plot1.values.xs = x_data; // this line is optional
		m_plot3.values.ys = m_SamplesTakenThree;
		m_plot3.values.count = stepIncreases;
		m_plot3.scale.min = 0;
		m_plot3.scale.max = Largest;
		m_plot3.tooltip.show = true;
		m_plot3.tooltip.format = "x=%.2f, y=%.2f";
		//m_plot3.grid_x.show = true;
		//m_plot3.grid_y.show = true;
		m_plot3.frame_size = ImVec2(400, 400);
		m_plot3.line_thickness = 1.f;

		m_PlotGeneratedTree = true;

		delete gameObjects;

	}

	if (m_PlotGeneratedTree)
	{
		//ImGui::Begin("Trash the cashe", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Plot("plot3", m_plot3);

		//ImGui::End();
	}
	//ImGui::EndChild();



	if (m_PlotGeneratedTree && m_PlotGeneratedTwo)
	{
		const float *Data[] = { m_SamplesTakenTwo,m_SamplesTakenThree };

		ImGui::PlotConfig CombinedPlot;

		CombinedPlot.values.ys_list = Data;
		CombinedPlot.values.ys_count = 2;
		CombinedPlot.values.count = 15;
		CombinedPlot.scale.min = 0;
		CombinedPlot.scale.max = m_Largest;
		CombinedPlot.tooltip.show = true;
		CombinedPlot.tooltip.format = "x=%.2f, y=%.2f";
		//m_plot3.grid_x.show = true;
		//m_plot3.grid_y.show = true;
		CombinedPlot.frame_size = ImVec2(400, 400);
		CombinedPlot.line_thickness = 1.f;

		ImGui::Plot("plotCombined", CombinedPlot);
	}


}
