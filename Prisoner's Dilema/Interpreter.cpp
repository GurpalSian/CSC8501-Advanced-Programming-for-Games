#include "Interpreter.h"



Interpreter::Interpreter()
{
	
}

Interpreter::~Interpreter()
{

}

int Interpreter::parse_line(std::string line, int* ptr, float* vars)
{
	_vars = vars;

	std::stringstream ss;

	int newVar;

	ss.str(line);

	std::string token;
	ss >> token; //line number
	ss >> token;

	if (token == "IF")
	{
		std::string arg1;
		ss >> arg1;

		std::string op;
		ss >> op;

		if (op == "+" || op == "-")
		{
			std::string arg2;
			ss >> arg2;

			newVar = evaluate_arithmetic_IF(arg1, op, arg2);

			std::getline(ss, line);

			parse_line(line, ptr, vars);

		}

		std::string arg2;
		ss >> arg2;

		if (evaluate_IF(arg1, op, arg2))
		{
			ss >> token;//GOTO
			ss >> token; //Line number
			*ptr = ((std::stoi(token) % 9) - 1);
			return 0;
		}
		else
		{
			(*ptr)++;
			return 0;
		}
	}
	else if (token == "BETRAY")
	{
		_decision = Betray;
		return 1;
	}
	else if (token == "SILENCE")
	{
		_decision = Silence;
		return 1;
	}
	else //token is RANDOM
	{
		int random = rand();

		int parity = random % 2;

		if (parity == 0)
		{
			_decision = Betray;
			return 1;
		}
		else
		{
			_decision = Silence;
			return 1;
		}
	}
}

bool Interpreter::evaluate_IF(std::string arg1, std::string op, std::string arg2)
{
	if (op == ">")
	{
		if (arg1 > arg2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (op == "<")
	{
		if (arg1 < arg2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (arg1 == arg2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

int Interpreter::evaluate_arithmetic_IF(std::string arg1, std::string op, std::string arg2)
{
	int argument1;
	int argument2;
	
	if (arg1 == "ALLOUTCOMES_W")
	{
		argument1 = _vars[0];
	}
	if (arg1 == "ALLOUTCOMES_X")
	{
		argument1 = _vars[1];
	}
	if (arg1 == "ALLOUTCOMES_Y")
	{
		argument1 = _vars[2];
	}
	if (arg1 == "ALLOUTCOMES_Z")
	{
		argument1 = _vars[3];
	}

	if (arg2 == "ALLOUTCOMES_W")
	{
		argument2 = _vars[0];
	}
	if (arg2 == "ALLOUTCOMES_X")
	{
		argument2 = _vars[1];
	}
	if (arg2 == "ALLOUTCOMES_Y")
	{
		argument2 = _vars[2];
	}
	if (arg2 == "ALLOUTCOMES_Z")
	{
		argument2 = _vars[3];
	}


	if (op == "+")
	{
		return argument1 + argument2;
	}
	else
	{
		return argument1 - argument2;
	}
}
