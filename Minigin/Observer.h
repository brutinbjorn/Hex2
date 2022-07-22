#pragma once

class BaseComponent;

namespace InterFace
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const std::string& msg) = 0;
	};
	
}

