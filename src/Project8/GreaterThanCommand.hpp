#pragma once
#include "Command.hpp"
#include "PopCommand.hpp"
#include "PushCommand.hpp"

class GreaterThanCommand : public Command
{
public:
	static int _counter;

	GreaterThanCommand(string segment = "", string arg1 = "", string arg2 = "")
		: Command(CommandType::GreaterThan, segment, arg1, arg2)
	{

	}

	virtual string ToAsm()
	{
		ostringstream result{};
		return result.str();
	}
};

int GreaterThanCommand::_counter = 0;