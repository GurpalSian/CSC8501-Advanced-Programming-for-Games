#include "Prisoner.h"

Prisoner::Prisoner()
{
	_myScore = 0.0f;
	_allOutcomes_W = 0.0f;
	_allOutcomes_X = 0.0f;
	_allOutcomes_Y = 0.0f;
	_allOutcomes_Z = 0.0f;

	_vars[0] = _allOutcomes_W;
	_vars[1] = _allOutcomes_X;
	_vars[2] = _allOutcomes_Y;
	_vars[3] = _allOutcomes_Z;
}

Prisoner::~Prisoner()
{
	
}

void Prisoner::run_strategy()
{
	_strategy->read_in_strategy_file();

	_decision = _strategy->parse_file(_vars);
}
void Prisoner::reset_strategy()
{ 
	_strategy->reset_strat(); 
}

std::ostream& operator<<(std::ostream& os, const Prisoner& p)
{
	os << "ALLOUTCOMES_W: " << p._allOutcomes_W << std::endl;
	os << "ALLOUTCOMES_X: " << p._allOutcomes_X << std::endl;
	os << "ALLOUTCOMES_Y: " << p._allOutcomes_Y << std::endl;
	os << "ALLOUTCOMES_Z: " << p._allOutcomes_Z << std::endl;
	os << "score: " << p._myScore << std::endl;
	os << std::endl;

	return os;
}
