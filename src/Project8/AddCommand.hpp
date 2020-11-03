#pragma once
#include "Command.hpp"
#include "PopCommand.hpp"
#include "PushCommand.hpp"

class AddCommand : public Command
{

public:
	AddCommand(string segment = "", string arg1 = "", string arg2 = "")
		: Command(CommandType::Add, segment, arg1, arg2)
	{

	}

	virtual string ToAsm()
	{
		/*
		BEFORE:
		        Z
				X 
		        Y
		        
		SP -> ___
		AFTER:
		        Z
				X+Y
		SP -> ___

		Example:
		        3
				5
				7
		SP -> ___
		-------------
		        3
				12
		SP -> ___
		*/
		ostringstream result{};

		//decrement stack pointer to get second value (Y)
		result << "@SP" << endl;
		result << "M=M-1" << endl;

		//grab the Y address, store Y value in D
		result << "A=M" << endl;
		result << "D=M" << endl;

		//decrement again to get first address (X)
		result << "@SP" << endl;
		result << "M=M-1" << endl;
		result << "A=M" << endl;

		//A points to X, D has value of Y
		result << "D=D+M" << endl;
		result << "@SP" << endl;
		result << "A=M" << endl;
		result << "M=D" << endl;

		//increment stack pointer
		result << "@SP" << endl;
		result << "M=M+1" << endl;

		return result.str();
	}
};