#pragma once
#include "Command.hpp"
#include "PopCommand.hpp"
#include "PushCommand.hpp"

class ReturnCommand : public Command
{
private:


public:
    ReturnCommand(string segment = "", string arg1 = "", string arg2 = "")
        : Command(CommandType::Return, segment, arg1, arg2)
    {

    }

    virtual string ToAsm()
    {
        ostringstream result{};
        return result.str();
    }
};