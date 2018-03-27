#include "Prisoner.h"
#include "StrategyGenerator.h"
#include "Tournament.h"
#include "Gang.h"

#include <limits>
#include <stdlib.h>
#include <time.h>

void read_menu(int menuNumber);
int catch_user_argument(int argNumber);

int main()
{
	srand((unsigned int)time(NULL));

	bool exit = false;
	int version = 0;
	int numOfStrats = 0;
	int numOfLines = 0;
	int numOfIterationsForGames = 0;

	StrategyGenerator stratgen;

	Tournament tournament;

	while (!exit)
	{
		read_menu(1);

		version = catch_user_argument(1);
		
		if (version != 0)
		{
			if (version == 1) //1V1
			{
				read_menu(2);

				numOfStrats = catch_user_argument(2);

				Prisoner* p1 = new Prisoner();
				Prisoner* p2 = new Prisoner();

				tournament.add_prisoners(p1, p2);

				read_menu(3);

				numOfLines = catch_user_argument(3);

				read_menu(4);

				numOfIterationsForGames = catch_user_argument(4);

				stratgen.generate_strategies(numOfStrats, numOfLines);

				tournament.run(numOfStrats, numOfIterationsForGames, version);

				tournament.print_tournament_results(version);

				tournament.reset_tournament();

				delete p1;
				p1 = nullptr;
				delete p2;
				p2 = nullptr;
			}
			else //GANG
			{
				read_menu(2);

				numOfStrats = catch_user_argument(2);

				Gang* g1 = new Gang();
				g1->set_gang_type(GangType::PurpleHandGang);
				Gang* g2 = new Gang();
				g2->set_gang_type(GangType::MagentaHandGang);

				tournament.add_gangs(g1, g2);

				read_menu(3);

				numOfLines = catch_user_argument(3);

				read_menu(4);

				numOfIterationsForGames = catch_user_argument(4);

				stratgen.generate_strategies(numOfStrats, numOfLines);

				tournament.run(numOfStrats, numOfIterationsForGames, version);

				tournament.print_tournament_results(version);

				tournament.reset_tournament();

				delete g1;
				g1 = nullptr;
				delete g2;
				g2 = nullptr;
			}
		}
		else
		{
			exit = true;
		}	
	}

	return 0;
}






void read_menu(int menuNumber)
{
	std::ifstream menu;
	std::string line;

	if (menuNumber == 1)
	{
		menu.open("..\\Menus\\VersionMenu.txt");
	}
	else if (menuNumber == 2)
	{
		menu.open("..\\Menus\\StrategyNumberMenu.txt");
	}
	else if (menuNumber == 3)
	{
		menu.open("..\\Menus\\LineNumberMenu.txt");
	}
	else
	{
		menu.open("..\\Menus\\NumberOfIterationsForGamesMenu.txt");
	}

	while (std::getline(menu, line))
	{
		std::cout << line << std::endl;
	}
}

int catch_user_argument(int argNumber)
{
	int value;

	do
	{
		while (!(std::cin >> value))
		{
			//user entered a non integer value
			std::cout << "Incorrect input. Please try again.\n";
			std::cin.clear(); //clears error flags set by incorrect input. If this is not called, the flags are not reset and the stream will continue to think it is in error mode
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove contents of stream after failure is caused. Clears the entire stream up to the newline character (default only clears first char)
		}
		if (value < 0) std::cout << "The number you entered is negative. Please enter a positive number to continue.\n";

		if (argNumber == 1)
		{
			if (value > 2)
			{
				std::cout << "Invalid version. Try again" << std::endl;
				value = -1;
			}
		}
		if (argNumber == 2)
		{
			if (value == 0)
			{
				std::cout << "Cannot have 0 strategy files\n";
				value = -1;
			}
		}
		if (argNumber == 3)
		{
			if (value == 0)
			{
				std::cout << "Cannot have 0 lines in a strategy file\n";
				value = -1;
			}
		}
		else if (argNumber == 4)
		{
			if (value == 0)
			{
				std::cout << "Cannot have 0 iterations for a game\n";
				value = -1;
			}
		}

	} while (value < 0);

	return value;
}