#pragma once
#include "Command.hpp"
#include "PopCommand.hpp"
#include "PushCommand.hpp"

class SubtractCommand : public Command
{
public:
    SubtractCommand(string segment = "", string arg1 = "", string arg2 = "")
        : Command(CommandType::Subtract, segment, arg1, arg2)
    {

    }

    virtual string ToAsm()
    {
        ostringstream result{};
        return result.str();
    }
};