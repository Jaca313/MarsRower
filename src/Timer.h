#pragma once
#include <chrono>

class Timer
{
private:
	float m_fTotalTime = 0.f;///< Total elapsed time since start of clock
	float m_fLoopTime = 0.f;///< Time since last frame

	std::chrono::system_clock::time_point m_start;
	std::chrono::system_clock::time_point m_end;
public:
	Timer(bool randomize = 0);///< Start Timer w/o random offset +- a second
	float Count();///<Update Clock

	float rloopTime();///< Returns time from last frame
	float rTotalTime();///< Returns total elapsed time
	float rClearTotalTime();///< Resets total elapsed time/returns previous

};

