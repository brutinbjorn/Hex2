#pragma once
#include <iostream>

#include "ActorComponent.h"


class Command
{
public:
	Command() = default;
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

//Fire", "Duck", "Jump", “Fart"

class DuckCommand  final : public Command
{
public:
	DuckCommand() = default;
	void Execute() override
	{
		std::cout << "player ducks." << std::endl;
	};
private:

};

class JumpCommand final : public Command
{
public:
	JumpCommand() = default;
	void Execute() override
	{
		std::cout << "player jumps." << std::endl;
	};
private:

};

class DieCommand final : public Command
{
public:
	DieCommand(ActorComponent* peter) : m_pPeter(peter){};

	void Execute() override
	{
		std::cout << "player dies" << std::endl;
	//	m_pPeter->Die();
	};
private:
	ActorComponent* m_pPeter = nullptr;
};

class ScoreTestCommand : public Command
{
public:
	ScoreTestCommand(ActorComponent* peter) : m_pPeter(peter) {};
	void Execute() override
	{

		std::cout << "player Score" << std::endl;
		//	m_pPeter->TestScore();
	}
private:
	ActorComponent* m_pPeter = nullptr;
};



class FireCommand final : public Command
{
public:
	FireCommand() = default;
	void Execute() override
	{
		std::cout << "player fires." << std::endl;
	};
private:

};

class FartCommand final : public Command
{
public:
	FartCommand() = default;
	void Execute() override
	{
		std::cout << "player farts." << std::endl;
	};
private:

};