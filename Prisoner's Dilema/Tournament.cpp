#include "Tournament.h"

#include <thread>

Tournament::Tournament()
{
	_iterations = 0;
}

Tournament::~Tournament()
{

}

void Tournament::add_prisoners(Prisoner* p1, Prisoner* p2)
{
	_prisonerOne = p1;
	_prisonerTwo = p2;
}

void Tournament::add_gangs(Gang* g1, Gang* g2)
{
	_gang1 = g1;
	_gang2 = g2;
}

void Tournament::run(int numOfStrats, int numOfIterations, int version)
{

	if (version == 1)
	{
		_numberOfIterationsPerGame = numOfIterations;

		for (int i = 0; i < numOfStrats; i++)
		{
			std::string path = std::string("..\\Strategies\\Strategy") + std::to_string(i + 1) + std::string(".txt");
			_prisonerOne->add_strategy(path, (i + 1));

			for (int j = i; j < numOfStrats; j++)
			{
				std::string path2 = std::string("..\\Strategies\\Strategy") + std::to_string(j + 1) + std::string(".txt");
				_prisonerTwo->add_strategy(path2, (j + 1));

				execute_game(numOfIterations, version);

				_prisonerTwo->remove_strategy();
			}
			_prisonerOne->remove_strategy();
		}

		save_tournament_results_to_file(version);
	}
	else
	{
		_numberOfIterationsPerGame = numOfIterations;

		for (int i = 0; i < _gang1->get_gang_members().size(); i++)
		{
			int strategyNumber = rand() % numOfStrats + 1;

			std::string path = std::string("..\\Strategies\\Strategy") + std::to_string(strategyNumber) + std::string(".txt");

			_gang1->get_gang_members()[i]->add_strategy(path, strategyNumber);
		}

		for (int i = 0; i < _gang2->get_gang_members().size(); i++)
		{
			int strategyNumber = rand() % numOfStrats + 1;

			std::string path2 = std::string("..\\Strategies\\Strategy") + std::to_string(strategyNumber) + std::string(".txt");

			_gang2->get_gang_members()[i]->add_strategy(path2, strategyNumber);
		}

		execute_game(numOfIterations, version);
	}
	
}

void Tournament::execute_game(int numOfIterations, int version)
{
	if (version == 1)
	{
		for (int i = 0; i < numOfIterations; i++)
		{
			
			std::thread thread1(&Prisoner::run_strategy, _prisonerOne); //first param is function pointer, second is the pointer which uses the function
			std::thread thread2(&Prisoner::run_strategy, _prisonerTwo);

			thread1.join(); //wait for first thread to return
			thread2.join(); //wait for second to finish

			increment_iterations();

			update_stats(version);

			std::thread thread3(&Prisoner::reset_strategy, _prisonerOne);
			std::thread thread4(&Prisoner::reset_strategy, _prisonerTwo);

			thread3.join();
			thread4.join();
		}
	}
	else
	{
		for (int i = 0; i < numOfIterations; i++)
		{

			std::thread thread1(&Gang::run_gang_strategy, _gang1);
			std::thread thread2(&Gang::run_gang_strategy, _gang2);

			thread1.join();
			thread2.join();

			increment_iterations();

			update_stats(version);

			std::thread thread3(&Gang::reset_gang_strategy, _gang1);
			std::thread thread4(&Gang::reset_gang_strategy, _gang2);

			thread3.join();
			thread4.join();

		}
	}
	
}

void Tournament::update_stats(int version)
{
	if (version == 1)
	{
		if (_prisonerOne->get_decision() == Decision::Silence && _prisonerTwo->get_decision() == Decision::Silence) //W
		{
			update_W();
		}
		else if (_prisonerOne->get_decision() == Decision::Silence && _prisonerTwo->get_decision() == Decision::Betray) //X and Y
		{
			update_X_and_Y();
		}
		else if (_prisonerOne->get_decision() == Decision::Betray && _prisonerTwo->get_decision() == Decision::Silence) //Y and X
		{
			update_Y_and_X();
		}
		else //Z
		{
			update_Z();
		}
	}
	else
	{
		if (_gang1->get_number_of_silences() == 5 && _gang2->get_number_of_silences() == 5)
		{
			update_gang_stats_all_silence();
		}
		if (_gang1->get_number_of_betrays() == 5 && _gang2->get_number_of_betrays() == 5)
		{
			update_gang_stats_all_betray();
		}
		if (_gang1->get_number_of_silences() == 5 && _gang2->get_number_of_betrays() == 5)
		{
			update_gang_stats_s_vs_b(_gang1, _gang2);
		}
		if (_gang1->get_number_of_betrays() == 5 && _gang2->get_number_of_silences() == 5)
		{
			update_gang_stats_s_vs_b(_gang2, _gang1);
		}
	}
}

void Tournament::update_gang_stats_all_silence()
{
	for (int i = 0; i < 4; i++)
	{
		_gang1->get_gang_members()[i]->set_LastOutcome(LastOutcome::W);
		_gang1->get_gang_members()[i]->increment_allOutcomes_W();

		_gang1->get_gang_members()[i]->set_my_score(2.0f);
		_gang1->get_gang_members()[i]->update_strategy_score(2.0f);

		_gang2->get_gang_members()[i]->set_LastOutcome(LastOutcome::W);
		_gang2->get_gang_members()[i]->increment_allOutcomes_W();

		_gang2->get_gang_members()[i]->set_my_score(2.0f);
		_gang2->get_gang_members()[i]->update_strategy_score(2.0f);
	}
}

void Tournament::update_gang_stats_all_betray()
{
	for (int i = 0; i < 4; i++)
	{
		_gang1->get_gang_members()[i]->set_LastOutcome(LastOutcome::Z);
		_gang1->get_gang_members()[i]->increment_allOutcomes_Z();

		_gang1->get_gang_members()[i]->set_my_score(4.0f);
		_gang1->get_gang_members()[i]->update_strategy_score(4.0f);

		_gang2->get_gang_members()[i]->set_LastOutcome(LastOutcome::Z);
		_gang2->get_gang_members()[i]->increment_allOutcomes_Z();

		_gang2->get_gang_members()[i]->set_my_score(4.0f);
		_gang2->get_gang_members()[i]->update_strategy_score(4.0f);
	}
}

void Tournament::update_gang_stats_s_vs_b(Gang* g1, Gang* g2)
{
	for (int i = 0; i < 4; i++)
	{
		g1->get_gang_members()[i]->set_LastOutcome(LastOutcome::X);
		g1->get_gang_members()[i]->increment_allOutcomes_X();

		g1->get_gang_members()[i]->set_my_score(5.0f);
		g1->get_gang_members()[i]->update_strategy_score(5.0f);

		g2->get_gang_members()[i]->set_LastOutcome(LastOutcome::Y);
		g2->get_gang_members()[i]->increment_allOutcomes_Y();

		g2->get_gang_members()[i]->set_my_score(0.0f);
		g2->get_gang_members()[i]->update_strategy_score(0.0f);
	}
}



void Tournament::update_W()
{
	_prisonerOne->set_LastOutcome(LastOutcome::W);
	_prisonerOne->increment_allOutcomes_W();

	_prisonerTwo->set_LastOutcome(LastOutcome::W);
	_prisonerTwo->increment_allOutcomes_W();

	_prisonerOne->set_my_score(2.0f);
	_prisonerOne->update_strategy_score(2.0f);

	_prisonerTwo->set_my_score(2.0f);
	_prisonerTwo->update_strategy_score(2.0f);
}

void Tournament::update_X_and_Y()
{
	_prisonerOne->set_LastOutcome(LastOutcome::X);
	_prisonerOne->increment_allOutcomes_X();

	_prisonerTwo->set_LastOutcome(LastOutcome::Y);
	_prisonerTwo->increment_allOutcomes_Y();

	_prisonerOne->set_my_score(5.0f);
	_prisonerOne->update_strategy_score(5.0f);
}

void Tournament::update_Y_and_X()
{
	_prisonerOne->set_LastOutcome(LastOutcome::Y);
	_prisonerOne->increment_allOutcomes_Y();

	_prisonerTwo->set_LastOutcome(LastOutcome::X);
	_prisonerTwo->increment_allOutcomes_X();

	_prisonerTwo->set_my_score(5.0f);
	_prisonerTwo->update_strategy_score(5.0f);
}

void Tournament::update_Z()
{
	_prisonerOne->set_LastOutcome(LastOutcome::Z);
	_prisonerOne->increment_allOutcomes_Z();

	_prisonerTwo->set_LastOutcome(LastOutcome::Z);
	_prisonerTwo->increment_allOutcomes_Z();

	_prisonerOne->set_my_score(4.0f);
	_prisonerOne->update_strategy_score(4.0f);

	_prisonerTwo->set_my_score(4.0f);
	_prisonerTwo->update_strategy_score(4.0f);
}

void Tournament::print_game_results()
{
	std::cout << std::endl;

	std::cout << "GAME RESULTS" << std::endl;

	std::cout << std::endl;

	std::cout << "Prisoner one stats" << std::endl;
	std::cout << *_prisonerOne << std::endl;

	std::cout << "Prisoner two stats" << std::endl;
	std::cout << *_prisonerTwo << std::endl;
}

void Tournament::print_tournament_results(int version)
{
	if (version == 1)
	{
		std::cout << std::endl;

		std::cout << "TOURNAMENT RESULTS" << std::endl;

		std::cout << std::endl;

		std::cout << "Prisoner one stats" << std::endl;
		std::cout << *_prisonerOne << std::endl;

		std::cout << "Prisoner two stats" << std::endl;
		std::cout << *_prisonerTwo << std::endl;

		std::cout << "Total number of games in this Tournament: " << get_iterations() / _numberOfIterationsPerGame << std::endl;
		std::cout << "Total number of iterations in this Tournament: " << get_iterations() << std::endl;

		std::cout << std::endl;
	}
	else
	{
		std::cout << std::endl;

		std::cout << "TOURNAMENT RESULTS" << std::endl;

		std::cout << std::endl;

		std::cout << "GANG 1" << std::endl;
		for (int i = 0; i < 4; i++)
		{
			std::cout << "Member " << i + 1 << " stats" << std::endl;
			std::cout << *(_gang1->get_gang_members()[i]) << std::endl;
		}

		std::cout << "GANG 2" << std::endl;
		for (int i = 0; i < 5; i++)
		{
			std::cout << "Member " << i + 1 << " stats" << std::endl;
			std::cout << *(_gang2->get_gang_members()[i]) << std::endl;
		}
	}
	
}

void Tournament::save_tournament_results_to_file(int version)
{

	if (version == 1)
	{
		std::ofstream file;

		file.open("..\\1V1 Tournament Results.txt");

		file << "Prisoner one stats" << std::endl;
		file << *_prisonerOne << std::endl;

		file << "Prisoner two stats" << std::endl;
		file << *_prisonerTwo << std::endl;

		file << "Total number of games in this Tournament: " << get_iterations() / _numberOfIterationsPerGame << std::endl;
		file << "Total number of iterations in this Tournament: " << get_iterations() << std::endl;

		file << std::endl;

		file.close();
	}
	else
	{

	}
	
}
