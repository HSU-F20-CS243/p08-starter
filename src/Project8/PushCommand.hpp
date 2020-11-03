#pragma once
#include <sstream>
#include <string>
#include <vector>
#include "Command.hpp"
using namespace std;

class PushCommand : public Command
{
private:
	string _file_name;

	void pushDToTopOfStack(ostringstream &str)
	{
		//store value on top of stack
		str << "@SP" << endl;
		str << "A=M" << endl;
		str << "M=D" << endl;
	}

public:
	PushCommand(string segment = "", string arg1 = "", string arg2 = "", string file_name = "")
		: Command(CommandType::Push, segment, arg1, arg2),
		_file_name(file_name)
	{

	}

	virtual string ToAsm()
	{
		ostringstream result{};

		//convert command into equivalent assembly
		switch (segment)
		{
		case Segment::Local:
			break;
		case Segment::Argument:
			break;
		case Segment::This:
			break;
		case Segment::That:
			break;
		case Segment::Temp:
			break;
		case Segment::Static:
			break;
		case Segment::Constant:

			//load the constant 
			result << "@" << arg1 << endl;
			result << "D=A" << endl;
			break;
		case Segment::Pointer:
			break;
		case Segment::GP1:
			result << "@" << Segment::GP1 << endl;
			result << "D=M" << endl;
			break;

		case Segment::GP2:
			result << "@" << Segment::GP2 << endl;
			result << "D=M" << endl;
			break;

		case Segment::GP3:
			result << "@" << Segment::GP3 << endl;
			result << "D=M" << endl;
			break;
		default:
			break;
		}

		//This will be okay IF each switch branch puts what it needs put on the stack in the 
		//D register
		pushDToTopOfStack(result);

		//increment stack pointer
		result << "@SP" << endl;
		result << "D=M+1" << endl;
		result << "M=D" << endl;
		
		return result.str();
	}
};
