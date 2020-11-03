#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <exception>
#include "Command.hpp"
using namespace std;

class PopCommand : public Command
{
private:
	string _file_name;


public:
	PopCommand(string segment = "", string arg1 = "", string arg2 = "", string file_name = "")
		: Command(CommandType::Pop, segment, arg1, arg2),
		_file_name(file_name)
	{

	}

	virtual string ToAsm()
	{
		ostringstream result{};

		//before you can grab the value, we need to decrement the stack pointer by 1
		result << "@SP" << endl;
		result << "M=M-1" << endl;

		switch (segment)
		{
		case Segment::None:
			break;
		case Segment::Stack:
			break;
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
			break;
		case Segment::Pointer:
			break;
		case Segment::GP1:
			throw "Cannot pop into GP1";
			break;
		case Segment::GP2:

			//load top value in stack into D
			result << "A=M" << endl;
			result << "D=M" << endl;

			//load GP2 register value into A
			result << "@" << Segment::GP2 << endl;
			result << "M=D" << endl;
			break;
		case Segment::GP3:

			//load top value in stack into D
			result << "A=M" << endl;
			result << "D=M" << endl;

			//load GP2 register value into A
			result << "@" << Segment::GP3 << endl;
			result << "M=D" << endl;
			break;
		default:
			break;
		}
		return result.str();
	}
};
