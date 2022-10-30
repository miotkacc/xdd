#pragma once

#include "TimerAbstractFactory.hpp"


struct SimpleTimerFactory: TimerAbstractFactory
{
    std::unique_ptr<ITimer> CreateOneShotTimer(std::function<void()>, std::chrono::duration<double, std::ratio<1,1>>);
    std::unique_ptr<ITimer> CreateRecurringTimer(std::function<void()>, std::chrono::duration<double, std::ratio<1,1>>);
};
