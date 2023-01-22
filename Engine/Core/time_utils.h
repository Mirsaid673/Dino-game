#pragma once

#include <chrono>

class Time
{
private:
    static std::chrono::_V2::system_clock::time_point last_time;
    static std::chrono::_V2::system_clock::time_point current_time;

public:
    static float delta_time;

    static void init();
    static void update();
};