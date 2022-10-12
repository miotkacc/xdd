#include <iostream>

#include "timer.hpp"


void SimpleTimer::start(){
        startTime = std::chrono::steady_clock::now();
        t = std::make_unique<std::thread>(&SimpleTimer::periodRunner, this);
}

void SimpleTimer::stop(){
        stopTimer = true;
        if(t and t->joinable())
        { 
            t->join();
        }
}

std::chrono::milliseconds SimpleTimer::getElapsedTime(const std::chrono::time_point<std::chrono::steady_clock>& start) const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
}

std::chrono::milliseconds SimpleTimer::getElapsedTime() const{
    return getElapsedTime(startTime);
}

SimpleTimer::~SimpleTimer()
{
    stop();
}

SimpleTimer::SimpleTimer(FunctionInfo functionInfo)
{
    functionCallInfo = FunctionCallInfo{functionInfo};
}

void SimpleTimer::periodRunner()
{
    functionCallInfo.lastTimeCalled = std::chrono::steady_clock::now();
    while(not stopTimer)
    {        
        std::this_thread::sleep_for(std::chrono::nanoseconds{900});
        if(getElapsedTime(functionCallInfo.lastTimeCalled) >= functionCallInfo.info.interval && (functionCallInfo.info.recurred || not functionCallInfo.called)){
            std::thread t1(functionCallInfo.info.funName);
            t1.detach();
            functionCallInfo.called = true;
            functionCallInfo.lastTimeCalled = std::chrono::steady_clock::now();
        }
    }
}
