#include "Gang.h"

Gang::Gang()
{
	create_gang();
	_numberOfBetrays = 0;
	_numberOfSilences = 0;
	_gangScore = 0.0f;
}

Gang::~Gang()
{
	for (int i = 0; i < _members.size(); i++)
	{
		delete _members[i];
		_members[i] = nullptr;
	}
}

void Gang::create_gang()
{
	_members.push_back(new Prisoner());
	_members.push_back(new Prisoner());
	_members.push_back(new Prisoner());
	_members.push_back(new Prisoner());
	_members.push_back(new Prisoner());
}

void Gang::run_gang_strategy()
{
	

	for (int i = 0; i < _members.size(); i++)
	{
		_members[i]->get_strategy()->read_in_strategy_file();

		_members[i]->set_decision(_members[i]->get_strategy()->parse_file(_members[i]->get_vars()));

		if (_members[i]->get_decision() == Decision::Betray)
		{
			_numberOfBetrays++;
		}
		if (_members[i]->get_decision() == Decision::Silence)
		{
			_numberOfSilences++;
		}
	}


	

	if (_numberOfBetrays == 5)
	{
		_gangDecision = Decision::Betray;
	}
	if (_numberOfSilences == 5)
	{
		_gangDecision = Decision::Silence;
	}


	
	
}

void Gang::reset_gang_strategy()
{
	for (int i = 0; i < _members.size(); i++)
	{
		_members[i]->reset_strategy();
	}

	_numberOfBetrays = 0;
	_numberOfSilences = 0;
}

std::ostream& operator<<(std::ostream& os, const Gang& g)
{
	os << "PRINTING GANG STATS" << std::endl;
	os << std::endl;

	int i = 1;
	for (std::vector<Prisoner*>::const_iterator it = g._members.begin(); it != g._members.end(); ++it)
	{
		os << "Gang member: " << i << std::endl;
		os << (*it) << std::endl;
		i++;
	}

	return os;
}
