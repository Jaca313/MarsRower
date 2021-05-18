#include "Timer.h"

Timer::Timer(bool randomize)
{
	m_start = std::chrono::system_clock::now();
	m_end = std::chrono::system_clock::now();

	m_fTotalTime = 0.f + randomize * rand() % 100 / 100.f;
	m_fLoopTime = 0.f;
}

float Timer::Count()
{
	m_end = std::chrono::system_clock::now();

	float duration = std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count() / 1000.f;
	m_fLoopTime  = duration;
	m_fTotalTime += duration;
	return duration;
}

float Timer::rloopTime()
{
	return m_fLoopTime;
}

float Timer::rTotalTime()
{
	return m_fTotalTime;
}

float Timer::rClearTotalTime()
{
	auto tempTime = m_fTotalTime;
	m_fTotalTime = 0.f;
	return m_fTotalTime;
}
