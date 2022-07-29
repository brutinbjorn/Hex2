#pragma once

namespace Alg
{
	class GraphConnection
	{
	public:
		GraphConnection() = default;
		~GraphConnection() = default;
		GraphConnection(const GraphConnection& other) = delete;
		GraphConnection(GraphConnection&& other) noexcept = delete;
		GraphConnection& operator=(const GraphConnection& other) = delete;
		GraphConnection& operator=(GraphConnection&& other) noexcept = delete;
	private:
		int m_from;
		int m_to;

	};
}

