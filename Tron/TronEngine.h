#pragma once
#include "Minigin.h"
class TronEngine : public dae::Minigin
{
public:
	TronEngine() = default;
	~TronEngine() = default;
	TronEngine(const TronEngine& other) = delete;
	TronEngine(TronEngine&& other) noexcept = delete;
	TronEngine& operator=(const TronEngine& other) = delete;
	TronEngine& operator=(TronEngine&& other) noexcept = delete;
	
	void LoadGame() override;;
private:


};

