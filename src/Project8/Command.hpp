#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

enum class CommandType { Push, Pop, Add, And, Equal, GreaterThan, LessThan, Negate, Not, Or, Subtract, Label, Goto, If, Function, Return, Call };
enum class Segment { None = -1, Stack, Local, Argument, This, That, Temp, Static, Constant, Pointer, GP1 = 13, GP2, GP3 };

ostream& operator<<(ostream& os, const Segment& seg)
{
	os << (int)seg;
	return os;
}

int operator+(const Segment& seg, int num)
{
	return (int)seg + num;
}


class Command
{
private:
	static unordered_map<string, Segment> _segments;
	static bool _has_init;

	void init()
	{
		_segments["argument"] = Segment::Argument;
		_segments["local"] = Segment::Local;
		_segments["static"] = Segment::Static;
		_segments["constant"] = Segment::Constant;
		_segments["this"] = Segment::This;
		_segments["that"] = Segment::That;
		_segments["pointer"] = Segment::Pointer;
		_segments["temp"] = Segment::Temp;
		_segments["gp1"] = Segment::GP1;
		_segments["gp2"] = Segment::GP2;
		_segments["gp3"] = Segment::GP3;
		_segments["none"] = Segment::None;
		_has_init = true;
	}

protected:

	static string _current_function;
	string _file_name;

	//From figure 8.6
	string buildLabel(string label)
	{
		ostringstream out{};
		out << _current_function << "$" << label;
		return out.str();
	}

	//Same as build but we put () around in order to define the label
	string defineLabel(string label)
	{
		ostringstream out{};
		out << "(" << buildLabel(label) << ")";
		return out.str();
	}

	//shortcut for defining a function name in ASM
	string defineFunction(string function_name)
	{
		ostringstream out{};
		out << "(" << function_name << ")";
		return out.str();
	}

	//used to track the current function 
	void setCurrentFunction(string function_name)
	{
		_current_function = function_name;
	}

	//used to define static variables in ASM
	string buildStaticVariableName(string static_var)
	{
		ostringstream out{};
		out << _file_name << "." << static_var;
		return out.str();
	}

	string buildStaticVariableName(int static_var)
	{
		ostringstream out{};
		out << _file_name << "." << static_var;
		return out.str();
	}

public:
	CommandType type;
	Segment segment;
	string arg1;
	string arg2;

	Command(CommandType type, string segment = "", string arg1 = "", string arg2 = "")
	{
		this->type = type;
		this->arg1 = arg1;
		this->arg2 = arg2;
		this->segment = Segment::None;

		if (_has_init == false)
		{
			init();
		}

		if (_segments.find(segment) != _segments.end())
		{
			this->segment = _segments[segment];
		}
	}

	void setFileName(const string& name)
	{
		_file_name = name;
	}

	string getFileName()
	{
		return _file_name;
	}

	virtual string ToAsm() = 0;
};

bool Command::_has_init = false;
unordered_map<string, Segment> Command::_segments;
string Command::_current_function;