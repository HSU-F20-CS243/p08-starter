/*PROJECT 8 NOTICE: 
* Replace this version of main with the current main.cpp once you're ready to transition into compiling 
* directories and "full" VM projects.

#include <vector>
#include <string>
#include <sstream>
#include <filesystem>

#include "Preprocessor.hpp"
#include "Command.hpp"
#include "CommandFactory.hpp"


//see https://stackoverflow.com/questions/50668814/vs2017-e0135-namespace-std-has-no-member-filesystem
//for forcing C++ 17 in VS 2019
namespace fs = std::filesystem;
using namespace std;

string removeQuotes(string in)
{
	istringstream input{ in };
	ostringstream output{};
	while (input.good() == true)
	{
		char temp;
		input >> temp;
		if (temp != '"')
		{
			output << temp;
		}
	}
	return output.str();
}

int main(int argc, char* argv[])
{
	vector<string> files_to_process{};

#ifdef _DEBUG
	//makes debugging easier by allowing you to directly load in files w/o using command line
	files_to_process.push_back("SimpleFunction.vm");
	ofstream output_file{ "SimpleFunction.asm" };

#else
	ofstream output_file{};
	string output_file_name = "";

	if (argc != 2)
	{
		cout << "Usage: PROGRAM.EXE <FILE.VM | DIRECTORY>" << endl;
		return -1;
	}
	auto pieces = StringSplitter::split(argv[1], ".");
	if (pieces.size() == 1)
	{
		//directory
		output_file_name = argv[1];
		for (auto item : fs::directory_iterator(argv[1]))
		{
			if (fs::is_directory(item.path()) == false)
			{
				ostringstream temp;
				temp << item.path().filename();
				string current_file = removeQuotes(temp.str());

				auto file_pieces = StringSplitter::split(current_file, ".");
				if (file_pieces.size() == 2 && file_pieces[1] == "vm")
				{
					temp = ostringstream{};
					temp << argv[1] << "/" << current_file;
					files_to_process.push_back(temp.str());
				}
			}
		}
	}
	else if (pieces.size() == 2)
	{
		files_to_process.push_back(argv[1]);
	}
	else
	{
		cout << "Unexpected file name: " << argv[1] << endl;
		return -1;
	}


	//file
	output_file_name = pieces[0];

	output_file_name += ".asm";
	output_file.open(output_file_name);

#endif // DEBUG

	//bootstrap: initialize SP to 256 and call
	//Sys.init
	output_file << "@256" << endl;
	output_file << "D=A" << endl;
	output_file << "@SP" << endl;
	output_file << "M=D" << endl;

	output_file << "@Sys.init" << endl;
	output_file << "0;JMP" << endl;

	for (auto file : files_to_process)
	{
		Preprocessor prep{ file };
		vector<vector<string>> program = prep.processFile();
		CommandFactory factory{};

		for (auto line : program)
		{
			Command* cmd = factory.fromVector(line);
			string code = cmd->ToAsm();
			delete cmd;
			output_file << code;
		}
	}

	output_file.close();
}
* */