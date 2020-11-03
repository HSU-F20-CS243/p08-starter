#pragma once
#include "Command.hpp"
#include "PopCommand.hpp"
#include "PushCommand.hpp"

class NotCommand : public Command
{
public:
    NotCommand(string segment = "", string arg1 = "", string arg2 = "")
        : Command(CommandType::Not, segment, arg1, arg2)
    {

    }

    virtual string ToAsm()
    {
        ostringstream result{};
        return result.str();
    }
};