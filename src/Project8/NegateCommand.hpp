#pragma once
#include "Command.hpp"
#include "PopCommand.hpp"
#include "PushCommand.hpp"

class NegateCommand : public Command
{
public:
    NegateCommand(string segment = "", string arg1 = "", string arg2 = "")
        : Command(CommandType::Negate, segment, arg1, arg2)
    {

    }

    virtual string ToAsm()
    {
        ostringstream result{};
        return result.str();
    }
};