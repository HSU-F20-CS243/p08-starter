#pragma once
#include "Command.hpp"
#include "PopCommand.hpp"
#include "PushCommand.hpp"

class LessThanCommand : public Command
{
public:
	static int _counter;

	LessThanCommand(string segment = "", string arg1 = "", string arg2 = "")
		: Command(CommandType::LessThan, segment, arg1, arg2)
	{

	}

	virtual string ToAsm()
	{
		ostringstream result{};
		return result.str();
	}
};

int LessThanCommand::_counter = 0;