#pragma once

#include "Prisoner.h"

enum GangType
{
	PurpleHandGang,
	MagentaHandGang
};

class Gang
{


public:


	Gang();
	
	~Gang();

	std::vector<Prisoner*> get_gang_members() { return _members; }

	void run_gang_strategy();
	void reset_gang_strategy();

	Decision get_gang_decision() { return _gangDecision; }

	int get_number_of_betrays() { return _numberOfBetrays; }
	int get_number_of_silences() { return _numberOfSilences; }

	void set_gang_type(GangType t) { _type = t; }
	GangType get_gang_type() { return _type; }

	friend std::ostream& operator<<(std::ostream& os, const Gang& g);

private:

	void create_gang();


private:

	int _numberOfBetrays;
	int _numberOfSilences;

	float _gangScore;

	Decision _gangDecision;
	LastOutcome _lastOutcome;

	std::vector<Prisoner*> _members; 

	GangType _type;

};


