#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


enum Decision
{
	Betray,
	Silence
};

class Interpreter
{
	

public:

	Interpreter();

	~Interpreter();

	int parse_line(std::string line, int* ptr, float* vars);

	bool evaluate_IF(std::string arg1, std::string op, std::string arg2);
	int evaluate_arithmetic_IF(std::string arg1, std::string op, std::string arg2);

	Decision get_decision() { return _decision; }



private:

	Decision _decision;
	float* _vars;

};

