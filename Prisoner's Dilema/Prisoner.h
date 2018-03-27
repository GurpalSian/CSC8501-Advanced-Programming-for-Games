#pragma once

#include "Strategy.h"

enum LastOutcome
{
	W, //I stayed silent and the other prisoner stayed silent	: 0
	X, //I stayed silent but the other prisoner betrayed me		: 1
	Y, //I betrayed the other prisoner while they stayed silent	: 2
	Z, //I betrayed the other prisoner and they betrayed me		: 3
	
	//Gang enums
	A, //I was in a gang with a mixed response where we had the most betrays
	B, //I was in a gang with a	mixed response where we	had	the	least betrays
	C  //I was in a gang with a mixed response where both gangs made cumulative equivalent decisions
};

class Prisoner
{

public:

	Prisoner();

	~Prisoner();

	void set_my_score(int score) { _myScore += score; }
	float get_my_score() { return _myScore; }

	void set_LastOutcome(LastOutcome lo) { _lastOutcome = lo; }
	LastOutcome get_LastOutcome() { return _lastOutcome; }

	void increment_allOutcomes_W() { _allOutcomes_W++; }
	void increment_allOutcomes_X() { _allOutcomes_X++; }
	void increment_allOutcomes_Y() { _allOutcomes_Y++; }
	void increment_allOutcomes_Z() { _allOutcomes_Z++; }

	float get_allOutcomes_W() { return _allOutcomes_W; }
	float get_allOutcomes_X() { return _allOutcomes_X; }
	float get_allOutcomes_Y() { return _allOutcomes_Y; }
	float get_allOutcomes_Z() { return _allOutcomes_Z; }

	void increment_allOutcomes_A() { _allOutcomes_A++; }
	void increment_allOutcomes_B() { _allOutcomes_B++; }
	void increment_allOutcomes_C() { _allOutcomes_C++; }

	float get_allOutcomes_A() { return _allOutcomes_A; }
	float get_allOutcomes_B() { return _allOutcomes_B; }
	float get_allOutcomes_C() { return _allOutcomes_C; }

	void add_strategy(std::string filepath, int ID) { _strategy = new Strategy(filepath, ID); }
	
	void remove_strategy() { delete _strategy; }
	Strategy* get_strategy() { return _strategy; }
	void run_strategy();
	void reset_strategy();
	void update_strategy_score(int score) { _strategy->update_strategy_score(score); }
	
	void set_decision(Decision d) { _decision = d; }
	Decision get_decision() { return _decision; }

	friend std::ostream& operator<<(std::ostream& os, const Prisoner& p);

	float* get_vars() { return _vars; }

protected:

	float _myScore;
	LastOutcome _lastOutcome;

	float _allOutcomes_W;
	float _allOutcomes_X;
	float _allOutcomes_Y;
	float _allOutcomes_Z;

	float _allOutcomes_A;
	float _allOutcomes_B;
	float _allOutcomes_C;

	Decision _decision;
	Strategy* _strategy;

	float _vars[4];

};



