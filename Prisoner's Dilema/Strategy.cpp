#include "Strategy.h"

Strategy::Strategy(std::string filepath, int ID)
{
	_strategyScore = 0.0f;
	_filepath = filepath;
	_strategyID = ID;
}

Strategy::~Strategy()
{
	
}

void Strategy::read_in_strategy_file()
{
	std::string line;

	_file.exceptions(std::ifstream::badbit); //failbit is for reading/writing file error

	try
	{
		_file.open(_filepath);

		while (std::getline(_file, line))
		{
			_lines.push_back(line);
		}

		_file.close();
	}
	catch (const std::ifstream::failure& e)
	{
		std::cerr << e.what() << std::endl;
		//e.what returns explanatory string
		//cerr is just a separate stream used for errors
		//By default stream failures don't throw exceptions so must be done manually
	}
	
}

Decision Strategy::parse_file(float* vars)
{
	int lineIndex = 0;
	int* ptr = &lineIndex;

	int success = 0;

	bool finished_parsing = false;

	while (!finished_parsing) 
	{
		success = _interpreter.parse_line(_lines[lineIndex], ptr, vars);

		if (success == 1)
		{
			finished_parsing = true;
		}
	}

	return _interpreter.get_decision();
}

void Strategy::reset_strat()
{
	_lines.clear();
}