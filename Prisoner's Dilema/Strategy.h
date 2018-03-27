#pragma once

#include "Interpreter.h"

#include <vector>


class Strategy
{

public:
	
	
	Strategy(std::string filepath, int ID);

	~Strategy();

	void read_in_strategy_file();
	Decision parse_file(float* vars);

	int get_strategy_ID() { return _strategyID; }

	void update_strategy_score(float score) { _strategyScore += score; }
	int get_strategy_score() { return _strategyScore; }

	void reset_strat();

private:

	int _strategyID;
	int _strategyScore;

	Interpreter _interpreter;
	
	std::vector<std::string> _lines;
	std::ifstream _file;

	Decision _decision;

	std::string _filepath;

};

