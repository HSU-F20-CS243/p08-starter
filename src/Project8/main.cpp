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

int main(int argc, char* argv[])
{
#ifdef _DEBUG
	//makes debugging easier by allowing you to directly load in files w/o using command line
	Preprocessor prep{ "OrTest.vm" };
	ofstream output_file{ "OrTest.asm" };
#else
	Preprocessor prep{};
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
		cout << "Directory parsing not yet implemented" << endl;
		return -1;

		//directory
		output_file_name = argv[1];
		for (auto item : fs::directory_iterator(argv[1]))
		{
			if (fs::is_directory(item.path()) == false)
			{
				cout << item.path().filename() << endl;
			}
		}

	}
	else if (pieces.size() == 2)
	{
		//file
		prep.load(argv[1]);
		output_file_name = pieces[0];
	}
	else
	{
		cout << "Unexpected file name: " << argv[1] << endl;
		return -1;
	}
	output_file_name += ".asm";
	output_file.open(output_file_name);



#endif // DEBUG

	vector<vector<string>> program = prep.processFile();
	CommandFactory factory{};

	for (auto line : program)
	{
		Command* cmd = factory.fromVector(line);
		string code = cmd->ToAsm();
		delete cmd;
		output_file << code;
	}

	output_file.close();
}