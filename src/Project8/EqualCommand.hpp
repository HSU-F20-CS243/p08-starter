#pragma once
#include "Command.hpp"
#include "PopCommand.hpp"
#include "PushCommand.hpp"

class EqualCommand : public Command
{
public:
	static int _counter;

	EqualCommand(string segment = "", string arg1 = "", string arg2 = "")
		: Command(CommandType::Equal, segment, arg1, arg2)
	{

	}

	virtual string ToAsm()
	{
		ostringstream result{};
		return result.str();
	}
};

int EqualCommand::_counter = 0;