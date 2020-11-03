#pragma once
#include "Command.hpp"
#include "PopCommand.hpp"
#include "PushCommand.hpp"

class OrCommand : public Command
{
public:
    OrCommand(string segment = "", string arg1 = "", string arg2 = "")
        : Command(CommandType::Or, segment, arg1, arg2)
    {

    }

    virtual string ToAsm()
    {
        ostringstream result{};

        //AC: Oops, I didn't mean to check in the answer.  Nonetheless, you aren't allowed to 
        //use this.  I will check this file and make sure that you write your OWN VERSION.
        PopCommand first{ "gp2" };
        PopCommand second{ "gp3" };
        PushCommand store{ "gp2" };

        result << first.ToAsm();
        result << second.ToAsm();
        result << "@" << Segment::GP2 << endl;
        result << "D=M" << endl;
        result << "@" << Segment::GP3 << endl;
        result << "D=D|M" << endl;
        result << "@" << Segment::GP2 << endl;
        result << "M=D" << endl;
        result << store.ToAsm();
        return result.str();
    }
};