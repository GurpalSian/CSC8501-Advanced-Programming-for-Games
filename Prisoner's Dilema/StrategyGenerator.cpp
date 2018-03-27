#include "StrategyGenerator.h"

StrategyGenerator::StrategyGenerator()
{
	
}

StrategyGenerator::~StrategyGenerator()
{

}

void StrategyGenerator::generate_strategies(int numOfStrats, int numOfLines)
{
	std::ofstream strat_file;

	for (int i = 1; i <= numOfStrats; i++)
	{
		std::string filepath = std::string("..\\Strategies\\") + std::string("Strategy") + std::to_string(numOfStrats - (numOfStrats - i)) + std::string(".txt");

		strat_file.open(filepath);

		generate_random_strategy(strat_file, numOfLines);

		strat_file.close();
	}
}

void StrategyGenerator::generate_random_strategy(std::ofstream& file, int numOfLines)
{
	int lines = generate_random_nummber_of_strategy_lines(numOfLines);
	
	generate_strategy_file_contents(file, lines);
}

int StrategyGenerator::generate_random_nummber_of_strategy_lines(int numOfLines)
{
	return rand() % numOfLines + 1;
}

void StrategyGenerator::generate_strategy_file_contents(std::ofstream& file, int lines)
{
	for (int i = 1; i <= (lines - 1); i++)
	{
		if (i == 1)
		{
			file << std::to_string(i) + std::string("0 ");
			file << generate_IF_statement(lines, i);
			continue;
		}
		file << std::to_string(i) + std::string("0 ");

		int parity = determine_type_of_keyword();
		_vectorOfParities.push_back(parity);

		if (parity == 0)
		{
			file << generate_final_action();
		}
		else
		{
			file << generate_IF_statement(lines, i);
		}
	}
	file << std::to_string(lines) + std::string("0 ");
	file << generate_final_action();
}

std::string StrategyGenerator::generate_final_action()
{
	int randomNumber = rand() % 3;

	if (randomNumber == 0)
	{
		return std::string("RANDOM\n");
	}
	if (randomNumber == 1)
	{
		return std::string("BETRAY\n");
	}
	if (randomNumber == 2)
	{
		return std::string("SILENCE\n");
	}
}

int StrategyGenerator::determine_type_of_keyword()
{
	int random = rand();
	int parity = random % 2;
	return parity;
}

std::string StrategyGenerator::generate_IF_statement(int numberOfLinesInStrategy, int currentLineNumber)
{
	int random = rand();

	int randomLineNumber = generate_random_nummber_of_strategy_lines(numberOfLinesInStrategy);
	while (currentLineNumber >= randomLineNumber)
	{
		randomLineNumber = generate_random_nummber_of_strategy_lines(numberOfLinesInStrategy);
	}
	
	if (random % 2 == 0)
	{
		return generate_IF_argument_type_one(randomLineNumber);
	}
	else
	{
		return generate_IF_argument_type_two(randomLineNumber);
	}
}

std::string StrategyGenerator::generate_IF_argument_type_one(int randomLineNumber)
{
	std::string line;

	std::string lhs = generate_random_alloutcomes();
	std::string rhs = generate_random_alloutcomes();

	while (lhs == rhs)
	{
		rhs = generate_random_alloutcomes();
	}

	line = std::string("IF ") + lhs + generate_random_operator() + rhs + std::string("GOTO ") + std::to_string(randomLineNumber) + std::string("0\n");

	return line;
}

std::string StrategyGenerator::generate_random_alloutcomes()
{
	int number = rand() % 4;

	if (number == 0)
	{
		return std::string("ALLOUTCOMES_W ");
	}
	if (number == 1)
	{
		return std::string("ALLOUTCOMES_X ");
	}
	if (number == 2)
	{
		return std::string("ALLOUTCOMES_Y ");
	}
	if (number == 3)
	{
		return std::string("ALLOUTCOMES_Z ");
	}
}

std::string StrategyGenerator::generate_random_operator()
{
	int number = rand() % 3;

	if (number == 0)
	{
		return std::string("< ");
	}
	if (number == 1)
	{
		return std::string("> ");
	}
	if (number == 2)
	{
		return std::string("= ");
	}
}

std::string StrategyGenerator::generate_IF_argument_type_two(int randomLineNumber)
{
	return std::string("IF LASTOUTCOME = ") + generate_random_last_outcome() + std::string("GOTO ") + std::to_string(randomLineNumber) + std::string("0\n");
}

std::string StrategyGenerator::generate_random_last_outcome()
{
	int number = rand() % 4;

	if (number == 0)
	{
		return std::string("W ");
	}
	if (number == 1)
	{
		return std::string("X ");
	}
	if (number == 2)
	{
		return std::string("Y ");
	}
	if (number == 3)
	{
		return std::string("Z ");
	}
}