#pragma once
#include "Command.hpp"
#include "PopCommand.hpp"
#include "PushCommand.hpp"

class LabelCommand : public Command
{
private:


public:
    LabelCommand(string segment = "", string arg1 = "", string arg2 = "")
        : Command(CommandType::Label, segment, arg1, arg2)
    {

    }

    //label should be in arg1
    virtual string ToAsm()
    {
        ostringstream result{};
        return result.str();
    }
};