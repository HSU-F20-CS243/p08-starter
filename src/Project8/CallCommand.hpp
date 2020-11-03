#pragma once
#include "Command.hpp"
#include "PopCommand.hpp"
#include "PushCommand.hpp"

class CallCommand : public Command
{
private:

public:
    CallCommand(string segment = "", string arg1 = "", string arg2 = "")
        : Command(CommandType::Call, segment, arg1, arg2)
    {

    }

    //function name should be in arg1
    //# arguments should be in arg2
    virtual string ToAsm()
    {
        ostringstream result{};
        return result.str();
    }
};