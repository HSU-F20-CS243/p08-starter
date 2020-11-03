#pragma once
#include "Command.hpp"
#include "PopCommand.hpp"
#include "PushCommand.hpp"

class AndCommand : public Command
{
public:
    AndCommand(string segment = "", string arg1 = "", string arg2 = "")
        : Command(CommandType::And, segment, arg1, arg2)
    {

    }

    virtual string ToAsm()
    {
        ostringstream result{};
        return result.str();
    }
};