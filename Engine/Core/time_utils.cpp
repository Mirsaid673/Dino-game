#include "time_utils.h"

std::chrono::_V2::system_clock::time_point Time::last_time;
std::chrono::_V2::system_clock::time_point Time::current_time;
float Time::delta_time = 0.0f;

void Time::init()
{
    current_time = last_time = std::chrono::high_resolution_clock::now();
};

void Time::update()
{
    last_time = current_time;
    current_time = std::chrono::high_resolution_clock::now();
    delta_time = std::chrono::duration<float, std::milli>(current_time - last_time).count() / 1000;
};