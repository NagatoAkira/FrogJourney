#ifndef DELTATIME_H_INCLUDED
#define DELTATIME_H_INCLUDED



#endif // DELTATIME_H_INCLUDED

#include <chrono>

// Define types for time measurement
using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;
using Duration = std::chrono::duration<float>; // Assuming we use float for precision

// Function to calculate delta time
float getDeltaTime() {
    static TimePoint prevTime = Clock::now(); // Initialize previous frame time statically

    // Get current time
    TimePoint currTime = Clock::now();

    // Calculate time difference between current and previous frame
    Duration deltaTime = std::chrono::duration_cast<Duration>(currTime - prevTime);

    // Update previous frame time for the next function call
    prevTime = currTime;

    // Return deltaTime in seconds
    return deltaTime.count();
}

void delayWithDeltatime(float framerate){
        float dt = getDeltaTime();

        // Use deltaTime to delay execution for a specific interval
        float desiredFrameTime = 1.0 / framerate; // Targeting 60 frames per second
        float remainingTime = desiredFrameTime - dt;
        if (remainingTime > 0) {
            delay(remainingTime*1000);
        }
}
