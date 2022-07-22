#include "MiniginPCH.h"
#include "JsonManager.h"

#pragma warning(push)
#pragma warning(disable:26812)
#pragma warning(disable:26819)
#pragma warning(disable:26800)
#include <nlohmann/json.hpp>
#pragma warning(pop)
#include <istream>
#include <fstream>

void JsonManager::Init(const std::string& Data)
{
	m_DataPath = Data;
}

nlohmann::json JsonManager::LoadJsonDoc(const std::string& file)
{
	const auto FullPath = m_DataPath + file;
	
	std::ifstream input(m_DataPath + file);
	if ((input.rdstate() & std::ifstream::failbit) != 0)
	{
		throw std::runtime_error(std::string("JSON File Not Found"));

	}
	if(!input.is_open())
		throw std::runtime_error(std::string(" File Not open"));

	nlohmann::json j;

	input >> j;
	std::cout << j.dump() << std::endl;
	return j;
}
