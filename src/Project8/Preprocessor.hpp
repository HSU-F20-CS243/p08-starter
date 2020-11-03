#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Preprocessor
{
private:
    string _file_to_process;

public:

    Preprocessor(string file_name)
        : _file_to_process(file_name)
    {
    }

    Preprocessor()
    {

    }

    void load(string file_name)
    {
        _file_to_process = file_name;
    }


    string removeComments(const string& text)
    {
        string result{ text };
        int index = result.find("//");
        return result.substr(0, index);
    }

    vector<vector<string>> processFile()
    {
        vector<vector<string>> result{};
        ifstream to_process{ _file_to_process };
        if (to_process.is_open() == true)
        {
            while (to_process.good() == true)
            {
                string line;
                getline(to_process, line);
                line = removeComments(line);
                istringstream input{ line };
                vector<string> current_line{};
                while (input.good() == true)
                {
                    string next;
                    input >> next;
                    if (next.length() > 0)
                    {
                        current_line.push_back(next);
                    }
                }
                if (current_line.size() > 0)
                {
                    result.push_back(current_line);
                }
                
            }
        }

        return result;
    }
};