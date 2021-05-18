#include "State.h"

bool State::quitState() const
{
	return m_bWantsQuit;
}

States State::requestState()
{
	States returnValue = m_iRequestState;
	m_iRequestState = States::INVALID;
	m_bResume = true;
	return returnValue;
}

States State::forceState() const
{
	return m_iForceState;
}

bool State::getResumeState()
{
	return m_bResume;
}

bool State::getRequestState()
{
	return m_iRequestState != States::INVALID;
}

States State::getID()
{
	return ID;
}
