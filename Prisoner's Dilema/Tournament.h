#pragma once

#include "Prisoner.h"
#include "Gang.h"


class Tournament
{

public:

	Tournament();
	~Tournament();

	void add_prisoners(Prisoner* p1, Prisoner* p2);
	void add_gangs(Gang* g1, Gang* g2);

	void run(int numOfStrats, int numOfIterations, int version);

	void print_tournament_results(int version);
	
	int get_iterations() { return _iterations; }
	void reset_tournament() { _iterations = 0; }
	
private:

	void execute_game(int numOfIterations, int version);

	void increment_iterations() { _iterations++; }

	void update_stats(int version);
	void update_W();
	void update_X_and_Y();
	void update_Y_and_X();
	void update_Z();

	void update_gang_stats_all_silence();
	void update_gang_stats_all_betray();
	void update_gang_stats_s_vs_b(Gang* g1, Gang* g2);

	void print_game_results();

	void save_tournament_results_to_file(int version);


	

private:

	Prisoner* _prisonerOne;
	Prisoner* _prisonerTwo;

	Gang* _gang1;
	Gang* _gang2;

	int _iterations;

	int _numberOfIterationsPerGame;

};

