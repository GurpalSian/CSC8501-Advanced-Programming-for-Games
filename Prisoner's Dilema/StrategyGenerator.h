#pragma once

#include <string>
#include <fstream>
#include <vector>

class StrategyGenerator
{

public:

	StrategyGenerator();
	~StrategyGenerator();

	void generate_strategies(int numOfStrats, int numOfLines);

private:

	
	void generate_random_strategy(std::ofstream& file, int numOfLines);
	int generate_random_nummber_of_strategy_lines(int numOfLines);
	void generate_strategy_file_contents(std::ofstream& file, int lines);

	int determine_type_of_keyword();
	std::string generate_final_action();
	std::string generate_IF_statement(int numberOfLinesInStrategy, int currentLineNumber);

	std::string generate_IF_argument_type_one(int randomLineNumber);
	std::string generate_random_alloutcomes();
	std::string generate_random_operator();

	std::string generate_IF_argument_type_two(int randomLineNumber);
	std::string generate_random_last_outcome();

	


private:

	std::vector<int> _vectorOfParities;

};

