#pragma once
#include "Command.hpp"
#include "StringSplitter.hpp"
#include "AddCommand.hpp"
#include "SubtractCommand.hpp"
#include "NegateCommand.hpp"
#include "EqualCommand.hpp"
#include "GreaterThanCommand.hpp"
#include "LessThanCommand.hpp"
#include "AndCommand.hpp"
#include "OrCommand.hpp"
#include "NotCommand.hpp"

#include "PopCommand.hpp"
#include "PushCommand.hpp"

#include "LabelCommand.hpp"
#include "IfCommand.hpp"
#include "GotoCommand.hpp"
#include "FunctionCommand.hpp"
#include "ReturnCommand.hpp"
#include "CallCommand.hpp"

#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <unordered_map>

using namespace std;
class CommandFactory
{

private:
    unordered_map < string, function<Command* (const string&, const string&, const string&, const string&)>> _commands{};


public:

    CommandFactory()
    {
        _commands["add"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new AddCommand(segment, arg1, arg2); cmd->setFileName(file_name); return cmd; };
        _commands["sub"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new SubtractCommand(segment, arg1, arg2); cmd->setFileName(file_name); return cmd; };
        _commands["neg"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new NegateCommand(segment, arg1, arg2); cmd->setFileName(file_name); return cmd; };
        _commands["eq"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new EqualCommand(segment, arg1, arg2); cmd->setFileName(file_name); return cmd; };
        _commands["gt"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new GreaterThanCommand(segment, arg1, arg2); cmd->setFileName(file_name); return cmd; };
        _commands["lt"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new LessThanCommand(segment, arg1, arg2); cmd->setFileName(file_name); return cmd; };
        _commands["and"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new AndCommand(segment, arg1, arg2); cmd->setFileName(file_name); return cmd; };
        _commands["or"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new OrCommand(segment, arg1, arg2); cmd->setFileName(file_name); return cmd; };
        _commands["not"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new NotCommand(segment, arg1, arg2); cmd->setFileName(file_name); return cmd; };
        
        _commands["push"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new PushCommand(segment, arg1, arg2); cmd->setFileName(file_name); return cmd; };
        _commands["pop"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new PopCommand(segment, arg1, arg2); cmd->setFileName(file_name); return cmd; };

        _commands["label"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new LabelCommand("none", segment, arg2); cmd->setFileName(file_name); return cmd; };
        _commands["if-goto"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new IfCommand("none", segment, arg2); cmd->setFileName(file_name); return cmd; };
        _commands["goto"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new GotoCommand("none", segment, arg2); cmd->setFileName(file_name); return cmd; };
        _commands["function"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new FunctionCommand("none", segment, arg1); cmd->setFileName(file_name); return cmd; };
        _commands["return"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new ReturnCommand("none", arg1, arg2); cmd->setFileName(file_name); return cmd; };
        _commands["call"] = [](const string& segment, const string& arg1, const string& arg2, const string& file_name) {Command* cmd = new CallCommand("none", segment, arg1); cmd->setFileName(file_name); return cmd; };

    }

    Command* fromVector(const vector<string>& text)
    {
        string segment = "";
        string arg1 = "";
        string arg2 = "";
        string file_name = "";

        if (text.size() > 1)
        {
            segment = text[1];
        }
        if (text.size() > 2)
        {
            arg1 = text[2];
        }
        if (text.size() > 3)
        {
            arg2 = text[3];
        }
        if (text.size() > 4)
        {
            file_name = text[4];
        }

        if (_commands.find(text[0]) != _commands.end())
        {
            return _commands[text[0]](segment, arg1, arg2, file_name);
        }
        return nullptr;
    }
};